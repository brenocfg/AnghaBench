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
struct TYPE_4__ {scalar_t__ jumps; int /*<<< orphan*/  addr; int /*<<< orphan*/  target; int /*<<< orphan*/  max_addr; int /*<<< orphan*/  min_addr; } ;
struct annotation {TYPE_2__ widths; TYPE_1__* options; } ;
struct TYPE_3__ {scalar_t__ show_nr_jumps; scalar_t__ use_offset; } ;

/* Variables and functions */

void annotation__update_column_widths(struct annotation *notes)
{
	if (notes->options->use_offset)
		notes->widths.target = notes->widths.min_addr;
	else
		notes->widths.target = notes->widths.max_addr;

	notes->widths.addr = notes->widths.target;

	if (notes->options->show_nr_jumps)
		notes->widths.addr += notes->widths.jumps + 1;
}