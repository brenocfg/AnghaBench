#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* view; TYPE_1__* model; } ;
struct TYPE_8__ {int refresh; } ;
struct TYPE_7__ {char** filter; int /*<<< orphan*/  n_filter; } ;
typedef  TYPE_3__ RPanel ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __reset_scroll_pos (TYPE_3__*) ; 
 int /*<<< orphan*/  __set_cmd_str_cache (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* __show_status_input (int /*<<< orphan*/ *,char*) ; 

void __set_filter(RCore *core, RPanel *panel) {
	if (!panel->model->filter) {
		return;
	}
	char *input = __show_status_input (core, "filter word: ");
	if (input) {
		panel->model->filter[panel->model->n_filter++] = input;
		__set_cmd_str_cache (core, panel, NULL);
		panel->view->refresh = true;
	}
	__reset_scroll_pos (panel);
}