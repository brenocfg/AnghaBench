#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct ltq_atm_ops {int /*<<< orphan*/  (* shutdown ) () ;int /*<<< orphan*/  (* stop ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__* port; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATM_PORT_NUMBER ; 
 int /*<<< orphan*/  PPE_MAILBOX_IGU1_INT ; 
 int /*<<< orphan*/  atm_dev_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_priv_data () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__ g_atm_priv_data ; 
 int /*<<< orphan*/ * ifx_mei_atm_showtime_enter ; 
 int /*<<< orphan*/ * ifx_mei_atm_showtime_exit ; 
 int /*<<< orphan*/  invalidate_oam_htu_entry () ; 
 struct ltq_atm_ops* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static int ltq_atm_remove(struct platform_device *pdev)
{
	int port_num;
	struct ltq_atm_ops *ops = platform_get_drvdata(pdev);

	ifx_mei_atm_showtime_enter = NULL;
	ifx_mei_atm_showtime_exit  = NULL;

	invalidate_oam_htu_entry();

	ops->stop(0);

	free_irq(PPE_MAILBOX_IGU1_INT, &g_atm_priv_data);

	for ( port_num = 0; port_num < ATM_PORT_NUMBER; port_num++ )
		atm_dev_deregister(g_atm_priv_data.port[port_num].dev);

	ops->shutdown();

	clear_priv_data();

	return 0;
}