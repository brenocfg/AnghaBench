#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct snd_seq_port_subscribe {int /*<<< orphan*/  dest; TYPE_1__ sender; } ;
struct snd_seq_client_port {int /*<<< orphan*/  c_src; } ;
struct snd_seq_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snd_seq_client_unlock (struct snd_seq_client*) ; 
 struct snd_seq_client* snd_seq_client_use_ptr (int /*<<< orphan*/ ) ; 
 int snd_seq_port_get_subscription (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct snd_seq_port_subscribe*) ; 
 int /*<<< orphan*/  snd_seq_port_unlock (struct snd_seq_client_port*) ; 
 struct snd_seq_client_port* snd_seq_port_use_ptr (struct snd_seq_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_seq_ioctl_get_subscription(struct snd_seq_client *client,
					  void *arg)
{
	struct snd_seq_port_subscribe *subs = arg;
	int result;
	struct snd_seq_client *sender = NULL;
	struct snd_seq_client_port *sport = NULL;

	result = -EINVAL;
	if ((sender = snd_seq_client_use_ptr(subs->sender.client)) == NULL)
		goto __end;
	if ((sport = snd_seq_port_use_ptr(sender, subs->sender.port)) == NULL)
		goto __end;
	result = snd_seq_port_get_subscription(&sport->c_src, &subs->dest,
					       subs);
      __end:
      	if (sport)
		snd_seq_port_unlock(sport);
	if (sender)
		snd_seq_client_unlock(sender);

	return result;
}