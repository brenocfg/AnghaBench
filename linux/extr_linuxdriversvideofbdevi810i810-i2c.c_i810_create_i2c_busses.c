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
struct i810fb_par {TYPE_1__* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  ddc_base; struct i810fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  GPIOC ; 
 int /*<<< orphan*/  i810_setup_i2c_bus (TYPE_1__*,char*) ; 

void i810_create_i2c_busses(struct i810fb_par *par)
{
        par->chan[0].par        = par;
	par->chan[1].par        = par;
	par->chan[2].par        = par;

	par->chan[0].ddc_base = GPIOA;
	i810_setup_i2c_bus(&par->chan[0], "I810-DDC");
	par->chan[1].ddc_base = GPIOB;
	i810_setup_i2c_bus(&par->chan[1], "I810-I2C");
	par->chan[2].ddc_base = GPIOC;
	i810_setup_i2c_bus(&par->chan[2], "I810-GPIOC");
}