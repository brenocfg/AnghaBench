#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Vcc; int Vpp; scalar_t__ flags; } ;
struct pcmcia_socket {int features; int /*<<< orphan*/  (* power_hook ) (struct pcmcia_socket*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev; TYPE_1__* ops; TYPE_2__ socket; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_status ) (struct pcmcia_socket*,int*) ;int /*<<< orphan*/  (* set_socket ) (struct pcmcia_socket*,TYPE_2__*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HOOK_POWER_POST ; 
 int /*<<< orphan*/  HOOK_POWER_PRE ; 
 int /*<<< orphan*/  SOCKET_CARDBUS ; 
 int SS_3VCARD ; 
 int SS_CAP_CARDBUS ; 
 int SS_CARDBUS ; 
 int SS_DETECT ; 
 int SS_PENDING ; 
 int SS_POWERON ; 
 int SS_XVCARD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int socket_reset (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*,int*) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*,int*) ; 
 int /*<<< orphan*/  stub3 (struct pcmcia_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct pcmcia_socket*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub5 (struct pcmcia_socket*,int*) ; 
 int /*<<< orphan*/  stub6 (struct pcmcia_socket*,int /*<<< orphan*/ ) ; 
 int vcc_settle ; 

__attribute__((used)) static int socket_setup(struct pcmcia_socket *skt, int initial_delay)
{
	int status, i;

	dev_dbg(&skt->dev, "setup\n");

	skt->ops->get_status(skt, &status);
	if (!(status & SS_DETECT))
		return -ENODEV;

	msleep(initial_delay * 10);

	for (i = 0; i < 100; i++) {
		skt->ops->get_status(skt, &status);
		if (!(status & SS_DETECT))
			return -ENODEV;

		if (!(status & SS_PENDING))
			break;

		msleep(100);
	}

	if (status & SS_PENDING) {
		dev_err(&skt->dev, "voltage interrogation timed out\n");
		return -ETIMEDOUT;
	}

	if (status & SS_CARDBUS) {
		if (!(skt->features & SS_CAP_CARDBUS)) {
			dev_err(&skt->dev, "cardbus cards are not supported\n");
			return -EINVAL;
		}
		skt->state |= SOCKET_CARDBUS;
	} else
		skt->state &= ~SOCKET_CARDBUS;

	/*
	 * Decode the card voltage requirements, and apply power to the card.
	 */
	if (status & SS_3VCARD)
		skt->socket.Vcc = skt->socket.Vpp = 33;
	else if (!(status & SS_XVCARD))
		skt->socket.Vcc = skt->socket.Vpp = 50;
	else {
		dev_err(&skt->dev, "unsupported voltage key\n");
		return -EIO;
	}

	if (skt->power_hook)
		skt->power_hook(skt, HOOK_POWER_PRE);

	skt->socket.flags = 0;
	skt->ops->set_socket(skt, &skt->socket);

	/*
	 * Wait "vcc_settle" for the supply to stabilise.
	 */
	msleep(vcc_settle * 10);

	skt->ops->get_status(skt, &status);
	if (!(status & SS_POWERON)) {
		dev_err(&skt->dev, "unable to apply power\n");
		return -EIO;
	}

	status = socket_reset(skt);

	if (skt->power_hook)
		skt->power_hook(skt, HOOK_POWER_POST);

	return status;
}