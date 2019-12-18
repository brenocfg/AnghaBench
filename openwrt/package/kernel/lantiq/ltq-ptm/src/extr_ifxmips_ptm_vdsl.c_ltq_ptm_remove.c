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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PPE_MAILBOX_IGU1_INT ; 
 int /*<<< orphan*/  clear_priv_data () ; 
 int /*<<< orphan*/  clear_tables () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** g_net_dev ; 
 int /*<<< orphan*/  g_ptm_priv_data ; 
 int /*<<< orphan*/ * ifx_mei_atm_showtime_enter ; 
 int /*<<< orphan*/ * ifx_mei_atm_showtime_exit ; 
 int /*<<< orphan*/  ifx_pp32_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifx_ptm_uninit_chip () ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ltq_ptm_remove(struct platform_device *pdev)
{
    int i;
	ifx_mei_atm_showtime_enter = NULL;
	ifx_mei_atm_showtime_exit  = NULL;


    ifx_pp32_stop(0);

    free_irq(PPE_MAILBOX_IGU1_INT, &g_ptm_priv_data);

    for ( i = 0; i < ARRAY_SIZE(g_net_dev); i++ )
        unregister_netdev(g_net_dev[i]);

    for ( i = 0; i < ARRAY_SIZE(g_net_dev); i++ ) {
        free_netdev(g_net_dev[i]);
        g_net_dev[i] = NULL;
    }

    clear_tables();

    ifx_ptm_uninit_chip();

    clear_priv_data();

    return 0;
}