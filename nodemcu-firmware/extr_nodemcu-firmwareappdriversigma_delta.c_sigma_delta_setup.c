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
 int /*<<< orphan*/  GPIO_REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPIO_SIGMA_DELTA ; 
 int /*<<< orphan*/  GPIO_SIGMA_DELTA_ENABLE ; 
 int GPIO_SIGMA_DELTA_PRESCALE_SET (int) ; 
 int GPIO_SIGMA_DELTA_SET (int /*<<< orphan*/ ) ; 
 int GPIO_SIGMA_DELTA_TARGET_SET (int) ; 

void sigma_delta_setup( void )
{
    GPIO_REG_WRITE(GPIO_SIGMA_DELTA,
                   GPIO_SIGMA_DELTA_SET(GPIO_SIGMA_DELTA_ENABLE) |
                   GPIO_SIGMA_DELTA_TARGET_SET(0x00) |
                   GPIO_SIGMA_DELTA_PRESCALE_SET(0x00));
}