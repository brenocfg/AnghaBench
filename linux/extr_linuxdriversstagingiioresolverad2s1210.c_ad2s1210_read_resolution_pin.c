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
struct ad2s1210_state {TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 unsigned char* ad2s1210_resolution_value ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char ad2s1210_read_resolution_pin(struct ad2s1210_state *st)
{
	int resolution = (gpio_get_value(st->pdata->res[0]) << 1) |
			  gpio_get_value(st->pdata->res[1]);

	return ad2s1210_resolution_value[resolution];
}