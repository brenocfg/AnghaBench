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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_net_dev ; 
 scalar_t__ g_showtime ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int ptm_showtime_exit(void)
{
    int i;

    if ( !g_showtime )
        return -1;

    for ( i = 0; i < ARRAY_SIZE(g_net_dev); i++ )
        netif_carrier_off(g_net_dev[i]);

    g_showtime = 0;

    printk("leave showtime\n");

    return 0;
}