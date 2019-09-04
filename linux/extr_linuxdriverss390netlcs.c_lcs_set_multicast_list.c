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
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
lcs_set_multicast_list(struct net_device *dev)
{
#ifdef CONFIG_IP_MULTICAST
        struct lcs_card *card;

        LCS_DBF_TEXT(4, trace, "setmulti");
        card = (struct lcs_card *) dev->ml_priv;

        if (!lcs_set_thread_start_bit(card, LCS_SET_MC_THREAD))
		schedule_work(&card->kernel_thread_starter);
#endif /* CONFIG_IP_MULTICAST */
}