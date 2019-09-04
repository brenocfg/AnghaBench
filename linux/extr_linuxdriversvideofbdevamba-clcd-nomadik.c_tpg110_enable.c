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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct clcd_fb {TYPE_1__* dev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpg110_read_reg (int) ; 
 int /*<<< orphan*/  tpg110_startup (struct device*) ; 
 int /*<<< orphan*/  tpg110_write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tpg110_enable(struct clcd_fb *fb)
{
	struct device *dev = &fb->dev->dev;
	static bool startup;
	u8 val;

	if (!startup) {
		tpg110_startup(dev);
		startup = true;
	}

	/* Take chip out of standby */
	val = tpg110_read_reg(0x03);
	val |= BIT(0);
	tpg110_write_reg(0x03, val);
}