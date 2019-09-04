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
struct arche_platform_drvdata {int wake_detect_state; } ;
typedef  enum svc_wakedetect_state { ____Placeholder_svc_wakedetect_state } svc_wakedetect_state ;

/* Variables and functions */

__attribute__((used)) static void arche_platform_set_wake_detect_state(
				struct arche_platform_drvdata *arche_pdata,
				enum svc_wakedetect_state state)
{
	arche_pdata->wake_detect_state = state;
}