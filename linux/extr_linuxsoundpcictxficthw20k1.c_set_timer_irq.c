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
 int /*<<< orphan*/  GIE ; 
 int /*<<< orphan*/  IT_INT ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_timer_irq(struct hw *hw, int enable)
{
	hw_write_20kx(hw, GIE, enable ? IT_INT : 0);
	return 0;
}