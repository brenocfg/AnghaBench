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
struct wilc_mac_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_mac ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

int wilc_wlan_cfg_init(void)
{
	memset((void *)&g_mac, 0, sizeof(struct wilc_mac_cfg));
	return 1;
}