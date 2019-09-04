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
typedef  int u32 ;
struct intelfb_info {int dummy; } ;
struct intelfb_i2c_chan {int /*<<< orphan*/  reg; struct intelfb_info* dinfo; } ;

/* Variables and functions */
 int INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDA_DIR_MASK ; 
 int SDA_VAL_IN ; 

__attribute__((used)) static int intelfb_gpio_getsda(void *data)
{
	struct intelfb_i2c_chan *chan = data;
	struct intelfb_info *dinfo = chan->dinfo;
	u32 val;

	OUTREG(chan->reg, SDA_DIR_MASK);
	OUTREG(chan->reg, 0);
	val = INREG(chan->reg);
	return ((val & SDA_VAL_IN) != 0);
}