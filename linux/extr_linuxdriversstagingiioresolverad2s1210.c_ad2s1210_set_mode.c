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
struct ad2s1210_state {int mode; TYPE_1__* pdata; } ;
typedef  enum ad2s1210_mode { ____Placeholder_ad2s1210_mode } ad2s1210_mode ;
struct TYPE_2__ {int /*<<< orphan*/ * a; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** ad2s1210_mode_vals ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ad2s1210_set_mode(enum ad2s1210_mode mode,
				     struct ad2s1210_state *st)
{
	gpio_set_value(st->pdata->a[0], ad2s1210_mode_vals[mode][0]);
	gpio_set_value(st->pdata->a[1], ad2s1210_mode_vals[mode][1]);
	st->mode = mode;
}