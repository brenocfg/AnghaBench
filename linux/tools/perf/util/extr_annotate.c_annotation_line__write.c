#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct annotation_write_ops {int /*<<< orphan*/  write_graph; int /*<<< orphan*/  printf; int /*<<< orphan*/  set_jumps_percent_color; int /*<<< orphan*/  set_percent_color; int /*<<< orphan*/  set_color; int /*<<< orphan*/  obj; int /*<<< orphan*/  width; int /*<<< orphan*/  change_color; int /*<<< orphan*/  current_entry; int /*<<< orphan*/  first_line; } ;
struct annotation_options {int /*<<< orphan*/  percent_type; } ;
struct annotation_line {int dummy; } ;
struct annotation {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __annotation_line__write (struct annotation_line*,struct annotation*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void annotation_line__write(struct annotation_line *al, struct annotation *notes,
			    struct annotation_write_ops *wops,
			    struct annotation_options *opts)
{
	__annotation_line__write(al, notes, wops->first_line, wops->current_entry,
				 wops->change_color, wops->width, wops->obj,
				 opts->percent_type,
				 wops->set_color, wops->set_percent_color,
				 wops->set_jumps_percent_color, wops->printf,
				 wops->write_graph);
}