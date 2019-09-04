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
 int /*<<< orphan*/  dispc_compat ; 
 int /*<<< orphan*/  dispc_free_irq (int /*<<< orphan*/ *) ; 

void dss_dispc_uninitialize_irq(void)
{
	dispc_free_irq(&dispc_compat);
}