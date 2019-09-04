#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pl022 {TYPE_2__* cur_chip; int /*<<< orphan*/  cur_cs; TYPE_1__* vendor; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cs_control ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ internal_cs_ctrl; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_cs_control (struct pl022*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pl022_cs_control(struct pl022 *pl022, u32 command)
{
	if (pl022->vendor->internal_cs_ctrl)
		internal_cs_control(pl022, command);
	else if (gpio_is_valid(pl022->cur_cs))
		gpio_set_value(pl022->cur_cs, command);
	else
		pl022->cur_chip->cs_control(command);
}