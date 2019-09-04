#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pcmcia_socket {struct bcm63xx_pcmcia_socket* driver_data; } ;
struct TYPE_3__ {int flags; } ;
struct bcm63xx_pcmcia_socket {int card_type; int /*<<< orphan*/  lock; TYPE_1__ requested_state; scalar_t__ card_detected; } ;
typedef  TYPE_1__ socket_state_t ;

/* Variables and functions */
 int CARD_CARDBUS ; 
 int /*<<< orphan*/  PCMCIA_C1_REG ; 
 int /*<<< orphan*/  PCMCIA_C1_RESET_MASK ; 
 int SS_RESET ; 
 int /*<<< orphan*/  pcmcia_readl (struct bcm63xx_pcmcia_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_writel (struct bcm63xx_pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bcm63xx_pcmcia_set_socket(struct pcmcia_socket *sock,
				     socket_state_t *state)
{
	struct bcm63xx_pcmcia_socket *skt;
	unsigned long flags;
	u32 val;

	skt = sock->driver_data;

	spin_lock_irqsave(&skt->lock, flags);

	/* note: hardware cannot control socket power, so we will
	 * always report SS_POWERON */

	/* apply socket reset */
	val = pcmcia_readl(skt, PCMCIA_C1_REG);
	if (state->flags & SS_RESET)
		val |= PCMCIA_C1_RESET_MASK;
	else
		val &= ~PCMCIA_C1_RESET_MASK;

	/* reverse reset logic for cardbus card */
	if (skt->card_detected && (skt->card_type & CARD_CARDBUS))
		val ^= PCMCIA_C1_RESET_MASK;

	pcmcia_writel(skt, val, PCMCIA_C1_REG);

	/* keep requested state for event reporting */
	skt->requested_state = *state;

	spin_unlock_irqrestore(&skt->lock, flags);

	return 0;
}