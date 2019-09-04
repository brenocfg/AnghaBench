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
struct lcs_card {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void lcs_clear_multicast_list(struct lcs_card *card)
{
#ifdef	CONFIG_IP_MULTICAST
	struct lcs_ipm_list *ipm;
	unsigned long flags;

	/* Free multicast list. */
	LCS_DBF_TEXT(3, setup, "clmclist");
	spin_lock_irqsave(&card->ipm_lock, flags);
	while (!list_empty(&card->ipm_list)){
		ipm = list_entry(card->ipm_list.next,
				 struct lcs_ipm_list, list);
		list_del(&ipm->list);
		if (ipm->ipm_state != LCS_IPM_STATE_SET_REQUIRED){
			spin_unlock_irqrestore(&card->ipm_lock, flags);
			lcs_send_delipm(card, ipm);
			spin_lock_irqsave(&card->ipm_lock, flags);
		}
		kfree(ipm);
	}
	spin_unlock_irqrestore(&card->ipm_lock, flags);
#endif
}