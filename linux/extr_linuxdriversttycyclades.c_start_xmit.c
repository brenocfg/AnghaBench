#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cyclades_port {int line; struct cyclades_card* card; } ;
struct cyclades_card {int first_line; int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CyCAR ; 
 int /*<<< orphan*/  CySRER ; 
 int CyTxRdy ; 
 int /*<<< orphan*/  cy_is_Z (struct cyclades_card*) ; 
 int cyy_readb (struct cyclades_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cyy_writeb (struct cyclades_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void start_xmit(struct cyclades_port *info)
{
	struct cyclades_card *card = info->card;
	unsigned long flags;
	int channel = info->line - card->first_line;

	if (!cy_is_Z(card)) {
		spin_lock_irqsave(&card->card_lock, flags);
		cyy_writeb(info, CyCAR, channel & 0x03);
		cyy_writeb(info, CySRER, cyy_readb(info, CySRER) | CyTxRdy);
		spin_unlock_irqrestore(&card->card_lock, flags);
	} else {
#ifdef CONFIG_CYZ_INTR
		int retval;

		spin_lock_irqsave(&card->card_lock, flags);
		retval = cyz_issue_cmd(card, channel, C_CM_INTBACK, 0L);
		if (retval != 0) {
			printk(KERN_ERR "cyc:start_xmit retval on ttyC%d was "
				"%x\n", info->line, retval);
		}
		spin_unlock_irqrestore(&card->card_lock, flags);
#else				/* CONFIG_CYZ_INTR */
		/* Don't have to do anything at this time */
#endif				/* CONFIG_CYZ_INTR */
	}
}