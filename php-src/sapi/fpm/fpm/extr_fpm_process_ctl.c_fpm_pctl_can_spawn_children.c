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
 scalar_t__ FPM_PCTL_STATE_NORMAL ; 
 scalar_t__ fpm_state ; 

int fpm_pctl_can_spawn_children() /* {{{ */
{
	return fpm_state == FPM_PCTL_STATE_NORMAL;
}