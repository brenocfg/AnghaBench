#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  clock; } ;
struct i2c_bit_adapter {TYPE_1__ mask; int /*<<< orphan*/  minfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  matroxfb_i2c_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void matroxfb_gpio_setscl(void* data, int state) {
	struct i2c_bit_adapter* b = data;
	matroxfb_i2c_set(b->minfo, b->mask.clock, state);
}