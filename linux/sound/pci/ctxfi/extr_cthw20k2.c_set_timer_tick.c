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
struct hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMR ; 
 unsigned int TIMR_IE ; 
 unsigned int TIMR_IP ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int set_timer_tick(struct hw *hw, unsigned int ticks)
{
	if (ticks)
		ticks |= TIMR_IE | TIMR_IP;
	hw_write_20kx(hw, TIMR, ticks);
	return 0;
}