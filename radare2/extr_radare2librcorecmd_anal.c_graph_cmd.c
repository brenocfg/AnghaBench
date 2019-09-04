#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getViewerPath () ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 char* r_file_path (char const*) ; 
 char* r_str_new (char*) ; 
 char* r_str_newf (char*,char*,char const*,char const*,char const*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static char* graph_cmd(RCore *core, char *r2_cmd, const char *save_path) {
	const char *dot = "dot";
	char *cmd = NULL;
	const char *ext = r_config_get (core->config, "graph.gv.format");
	char *dotPath = r_file_path (dot);
	if (!strcmp (dotPath, dot)) {
		free (dotPath);
		dot = "xdot";
		dotPath = r_file_path (dot);
		if (!strcmp (dotPath, dot)) {
			free (dotPath);
			return r_str_new ("agf");
		}
	}
	if (save_path && *save_path) {
		cmd = r_str_newf ("%s > a.dot;!%s -T%s -o%s a.dot;",
			r2_cmd, dot, ext, save_path);
	} else {
		char *viewer = getViewerPath();
		if (viewer) {
			cmd = r_str_newf ("%s > a.dot;!%s -T%s -oa.%s a.dot;!%s a.%s",
				r2_cmd, dot, ext, ext, viewer, ext);
			free (viewer);
		} else {
			eprintf ("Cannot find a valid picture viewer\n");
		}
	}
	free (dotPath);
	return cmd;
}