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
 scalar_t__ APPS_RCM_O_APPS_RCM_INTERRUPT_STATUS ; 
 scalar_t__ ARCM_BASE ; 
 unsigned long HWREG (scalar_t__) ; 

unsigned long PRCMIntStatus(void)
{
    return HWREG(ARCM_BASE + APPS_RCM_O_APPS_RCM_INTERRUPT_STATUS);
}