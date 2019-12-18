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
 int /*<<< orphan*/  I2C_IF_WLOCK ; 
 scalar_t__ STATE_LOCKED ; 
 scalar_t__ hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hw20k2_i2c_lock_chip(struct hw *hw)
{
	/* Write twice */
	hw_write_20kx(hw, I2C_IF_WLOCK, STATE_LOCKED);
	hw_write_20kx(hw, I2C_IF_WLOCK, STATE_LOCKED);
	if (hw_read_20kx(hw, I2C_IF_WLOCK) == STATE_LOCKED)
		return 0;

	return -1;
}