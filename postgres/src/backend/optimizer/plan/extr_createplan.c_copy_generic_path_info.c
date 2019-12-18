#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parallel_safe; int /*<<< orphan*/  parallel_aware; TYPE_1__* pathtarget; int /*<<< orphan*/  rows; int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; } ;
struct TYPE_7__ {int /*<<< orphan*/  parallel_safe; int /*<<< orphan*/  parallel_aware; int /*<<< orphan*/  plan_width; int /*<<< orphan*/  plan_rows; int /*<<< orphan*/  total_cost; int /*<<< orphan*/  startup_cost; } ;
struct TYPE_6__ {int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ Plan ;
typedef  TYPE_3__ Path ;

/* Variables and functions */

__attribute__((used)) static void
copy_generic_path_info(Plan *dest, Path *src)
{
	dest->startup_cost = src->startup_cost;
	dest->total_cost = src->total_cost;
	dest->plan_rows = src->rows;
	dest->plan_width = src->pathtarget->width;
	dest->parallel_aware = src->parallel_aware;
	dest->parallel_safe = src->parallel_safe;
}