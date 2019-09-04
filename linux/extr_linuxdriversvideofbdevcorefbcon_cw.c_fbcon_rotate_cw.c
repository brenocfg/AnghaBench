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
struct fbcon_ops {int /*<<< orphan*/  update_start; int /*<<< orphan*/  cursor; int /*<<< orphan*/  clear_margins; int /*<<< orphan*/  putcs; int /*<<< orphan*/  clear; int /*<<< orphan*/  bmove; } ;

/* Variables and functions */
 int /*<<< orphan*/  cw_bmove ; 
 int /*<<< orphan*/  cw_clear ; 
 int /*<<< orphan*/  cw_clear_margins ; 
 int /*<<< orphan*/  cw_cursor ; 
 int /*<<< orphan*/  cw_putcs ; 
 int /*<<< orphan*/  cw_update_start ; 

void fbcon_rotate_cw(struct fbcon_ops *ops)
{
	ops->bmove = cw_bmove;
	ops->clear = cw_clear;
	ops->putcs = cw_putcs;
	ops->clear_margins = cw_clear_margins;
	ops->cursor = cw_cursor;
	ops->update_start = cw_update_start;
}