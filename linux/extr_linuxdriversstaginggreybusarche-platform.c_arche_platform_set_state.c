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
struct arche_platform_drvdata {int state; } ;
typedef  enum arche_platform_state { ____Placeholder_arche_platform_state } arche_platform_state ;

/* Variables and functions */

__attribute__((used)) static void arche_platform_set_state(struct arche_platform_drvdata *arche_pdata,
				     enum arche_platform_state state)
{
	arche_pdata->state = state;
}