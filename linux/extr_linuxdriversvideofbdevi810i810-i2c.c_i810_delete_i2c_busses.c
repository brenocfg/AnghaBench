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
struct TYPE_2__ {int /*<<< orphan*/ * par; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

void i810_delete_i2c_busses(struct i810fb_par *par)
{
        if (par->chan[0].par)
		i2c_del_adapter(&par->chan[0].adapter);
        par->chan[0].par = NULL;

	if (par->chan[1].par)
		i2c_del_adapter(&par->chan[1].adapter);
	par->chan[1].par = NULL;

	if (par->chan[2].par)
		i2c_del_adapter(&par->chan[2].adapter);
	par->chan[2].par = NULL;
}