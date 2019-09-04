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
struct ds1wm_data {int /*<<< orphan*/  pdev; TYPE_1__* cell; int /*<<< orphan*/  int_en_reg_none; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DS1WM_INT_EN ; 
 int /*<<< orphan*/  ds1wm_reset (struct ds1wm_data*) ; 
 int /*<<< orphan*/  ds1wm_write_register (struct ds1wm_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds1wm_down(struct ds1wm_data *ds1wm_data)
{
	ds1wm_reset(ds1wm_data);

	/* Disable interrupts. */
	ds1wm_write_register(ds1wm_data, DS1WM_INT_EN,
		ds1wm_data->int_en_reg_none);

	if (ds1wm_data->cell->disable)
		ds1wm_data->cell->disable(ds1wm_data->pdev);
}