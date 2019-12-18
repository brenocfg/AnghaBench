#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* context; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int i_value; int /*<<< orphan*/  value; } ;
struct TYPE_7__ {TYPE_4__* print; } ;
struct TYPE_6__ {int color_mode; } ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RConfigNode ;

/* Variables and functions */
 int COLOR_MODE_16M ; 
 int /*<<< orphan*/  R_PRINT_FLAGS_COLOR ; 
 int /*<<< orphan*/  r_cons_pal_update_event () ; 
 TYPE_5__* r_cons_singleton () ; 
 int /*<<< orphan*/  r_print_set_flags (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool cb_color(void *user, void *data) {
	RCore *core = (RCore *) user;
	RConfigNode *node = (RConfigNode *) data;
	if (node->i_value) {
		core->print->flags |= R_PRINT_FLAGS_COLOR;
	} else {
		core->print->flags &= (~R_PRINT_FLAGS_COLOR);
	}
	if (!strcmp (node->value, "true")) {
		node->i_value = 1;
	} else if (!strcmp (node->value, "false")) {
		node->i_value = 0;
	}
	r_cons_singleton ()->context->color_mode = (node->i_value > COLOR_MODE_16M)
		? COLOR_MODE_16M: node->i_value;
	r_cons_pal_update_event ();
	r_print_set_flags (core->print, core->print->flags);
	return true;
}