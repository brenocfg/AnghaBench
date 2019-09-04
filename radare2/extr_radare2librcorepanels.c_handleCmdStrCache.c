#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* model; } ;
struct TYPE_6__ {scalar_t__ cache; } ;
typedef  TYPE_2__ RPanel ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 scalar_t__ R_STR_ISNOTEMPTY (char*) ; 
 char* apply_filter_cmd (TYPE_2__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_core_cmd_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  setCmdStrCache (TYPE_2__*,char*) ; 

char *handleCmdStrCache(RCore *core, RPanel *panel) {
	char *out;
	char *cmd = apply_filter_cmd (panel);
	out = r_core_cmd_str (core, cmd);
	if (panel->model->cache && R_STR_ISNOTEMPTY (out)) {
		setCmdStrCache (panel, out);
	}
	free (cmd);
	return out;
}