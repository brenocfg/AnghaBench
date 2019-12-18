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
 int /*<<< orphan*/  o2hb_unregister_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2net_hb_down ; 
 int /*<<< orphan*/  o2net_hb_up ; 

void o2net_unregister_hb_callbacks(void)
{
	o2hb_unregister_callback(NULL, &o2net_hb_up);
	o2hb_unregister_callback(NULL, &o2net_hb_down);
}