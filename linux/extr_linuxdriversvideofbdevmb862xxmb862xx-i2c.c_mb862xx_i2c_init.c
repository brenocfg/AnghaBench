#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mb862xxfb_par {TYPE_1__* adap; } ;
struct TYPE_3__ {struct mb862xxfb_par* algo_data; } ;

/* Variables and functions */
 int i2c_add_adapter (TYPE_1__*) ; 
 TYPE_1__ mb862xx_i2c_adapter ; 

int mb862xx_i2c_init(struct mb862xxfb_par *par)
{
	mb862xx_i2c_adapter.algo_data = par;
	par->adap = &mb862xx_i2c_adapter;

	return i2c_add_adapter(par->adap);
}