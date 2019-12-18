#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  prompt_type; } ;
struct TYPE_6__ {TYPE_1__* cons; } ;
struct TYPE_5__ {TYPE_3__* line; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_LINE_PROMPT_DEFAULT ; 
 int /*<<< orphan*/  R_LINE_PROMPT_FILE ; 
 int /*<<< orphan*/  __add_cmdf_panel (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  __file_history_down ; 
 int /*<<< orphan*/  __file_history_up ; 
 int /*<<< orphan*/  r_line_hist_cmd_down ; 
 int /*<<< orphan*/  r_line_hist_cmd_up ; 
 int /*<<< orphan*/  r_line_set_hist_callback (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int __open_file_cb(void *user) {
	RCore *core = (RCore *)user;
	core->cons->line->prompt_type = R_LINE_PROMPT_FILE;
	r_line_set_hist_callback (core->cons->line, &__file_history_up, &__file_history_down);
	__add_cmdf_panel (core, "open file: ", "o %s");
	core->cons->line->prompt_type = R_LINE_PROMPT_DEFAULT;
	r_line_set_hist_callback (core->cons->line, &r_line_hist_cmd_up, &r_line_hist_cmd_down);
	return 0;
}