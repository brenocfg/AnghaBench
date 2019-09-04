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
struct ad2s1210_state {int resolution; TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** ad2s1210_res_pins ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ad2s1210_set_resolution_pin(struct ad2s1210_state *st)
{
	gpio_set_value(st->pdata->res[0],
		       ad2s1210_res_pins[(st->resolution - 10) / 2][0]);
	gpio_set_value(st->pdata->res[1],
		       ad2s1210_res_pins[(st->resolution - 10) / 2][1]);
}