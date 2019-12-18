#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  replace ;
struct TYPE_14__ {int /*<<< orphan*/  panels; } ;
struct TYPE_13__ {TYPE_2__* view; TYPE_1__* model; } ;
struct TYPE_12__ {int refresh; } ;
struct TYPE_11__ {int rotate; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 TYPE_3__* __get_cur_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __reset_filter (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  __set_cmd_str_cache (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* r_str_between (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  r_str_dup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_str_replace (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

void __rotate_panel_cmds(RCore *core, const char **cmds, const int cmdslen, const char *prefix, bool rev) {
	if (!cmdslen) {
		return;
	}
	RPanel *p = __get_cur_panel (core->panels);
	__reset_filter (core, p);
	if (rev) {
		if (!p->model->rotate) {
			p->model->rotate = cmdslen - 1;
		} else {
			p->model->rotate--;
		}
	} else {
		p->model->rotate++;
	}
	char tmp[64], *between;
	int i = p->model->rotate % cmdslen;
	snprintf (tmp, sizeof (tmp), "%s%s", prefix, cmds[i]);
	between = r_str_between (p->model->cmd, prefix, " ");
	if (between) {
		char replace[64];
		snprintf (replace, sizeof (replace), "%s%s", prefix, between);
		p->model->cmd = r_str_replace (p->model->cmd, replace, tmp, 1);
	} else {
		p->model->cmd = r_str_dup (p->model->cmd, tmp);
	}
	__set_cmd_str_cache (core, p, NULL);
	p->view->refresh = true;
}