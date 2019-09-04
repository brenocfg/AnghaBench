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
struct riva_par {TYPE_1__* chan; } ;
struct TYPE_2__ {int ddc_base; struct riva_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  riva_setup_i2c_bus (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

void riva_create_i2c_busses(struct riva_par *par)
{
	par->chan[0].par	= par;
	par->chan[1].par	= par;
	par->chan[2].par        = par;

	par->chan[0].ddc_base = 0x36;
	par->chan[1].ddc_base = 0x3e;
	par->chan[2].ddc_base = 0x50;
	riva_setup_i2c_bus(&par->chan[0], "BUS1", I2C_CLASS_HWMON);
	riva_setup_i2c_bus(&par->chan[1], "BUS2", 0);
	riva_setup_i2c_bus(&par->chan[2], "BUS3", 0);
}