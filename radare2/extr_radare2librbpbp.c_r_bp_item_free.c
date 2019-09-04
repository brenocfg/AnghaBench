#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* cond; struct TYPE_4__* data; struct TYPE_4__* module_name; struct TYPE_4__* obytes; struct TYPE_4__* bbytes; struct TYPE_4__* name; } ;
typedef  TYPE_1__ RBreakpointItem ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void r_bp_item_free (RBreakpointItem *b) {
	free (b->name);
	free (b->bbytes);
	free (b->obytes);
	free (b->module_name);
	free (b->data);
	free (b->cond);
	free (b);
}