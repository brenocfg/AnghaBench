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
typedef  int /*<<< orphan*/  u32 ;
struct intelfb_info {int dummy; } ;
struct intelfb_i2c_chan {int /*<<< orphan*/  reg; struct intelfb_info* dinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 
 int SCL_DIR ; 
 int SCL_DIR_MASK ; 
 int SCL_VAL_MASK ; 
 int SCL_VAL_OUT ; 

__attribute__((used)) static void intelfb_gpio_setscl(void *data, int state)
{
	struct intelfb_i2c_chan *chan = data;
	struct intelfb_info *dinfo = chan->dinfo;
	u32 val;

	OUTREG(chan->reg, (state ? SCL_VAL_OUT : 0) |
	       SCL_DIR | SCL_DIR_MASK | SCL_VAL_MASK);
	val = INREG(chan->reg);
}