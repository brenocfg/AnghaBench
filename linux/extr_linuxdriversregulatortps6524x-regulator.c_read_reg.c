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
struct tps6524x {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __read_reg (struct tps6524x*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_reg(struct tps6524x *hw, int reg)
{
	int ret;

	mutex_lock(&hw->lock);
	ret = __read_reg(hw, reg);
	mutex_unlock(&hw->lock);

	return ret;
}