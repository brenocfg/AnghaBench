#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ ctxactive; } ;
struct TYPE_8__ {char* c_path; char* c_last; char* c_name; TYPE_1__ c_cfg; } ;
struct TYPE_7__ {int curctx; } ;

/* Variables and functions */
 int CTX_MAX ; 
 int FALSE ; 
 int /*<<< orphan*/  F_NORMAL ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int TRUE ; 
 TYPE_2__ cfg ; 
 int /*<<< orphan*/  close (int) ; 
 size_t cur ; 
 TYPE_4__* dents ; 
 char* g_buf ; 
 TYPE_3__* g_ctx ; 
 int /*<<< orphan*/  g_pipepath ; 
 int g_plinit ; 
 int /*<<< orphan*/  mkpath (int /*<<< orphan*/ ,char const*,char*) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plctrl_init () ; 
 int /*<<< orphan*/  plugindir ; 
 size_t read (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savecurctx (TYPE_2__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spawn (char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool run_selected_plugin(char **path, const char *file, char *newpath, char *runfile, char **lastname, char **lastdir)
{
	int fd;
	size_t len;

	if (!g_plinit) {
		plctrl_init();
		g_plinit = TRUE;
	}

	fd = open(g_pipepath, O_RDONLY | O_NONBLOCK);
	if (fd == -1)
		return FALSE;

	/* Generate absolute path to plugin */
	mkpath(plugindir, file, newpath);

	if (runfile && runfile[0]) {
		xstrlcpy(*lastname, runfile, NAME_MAX);
		spawn(newpath, *lastname, *path, *path, F_NORMAL);
	} else
		spawn(newpath, NULL, *path, *path, F_NORMAL);

	len = read(fd, g_buf, PATH_MAX);
	g_buf[len] = '\0';

	close(fd);

	if (len > 1) {
		int ctx = g_buf[0] - '0';

		if (ctx == 0 || ctx == cfg.curctx + 1) {
			xstrlcpy(*lastdir, *path, PATH_MAX);
			xstrlcpy(*path, g_buf + 1, PATH_MAX);
		} else if (ctx >= 1 && ctx <= CTX_MAX) {
			int r = ctx - 1;

			g_ctx[r].c_cfg.ctxactive = 0;
			savecurctx(&cfg, g_buf + 1, dents[cur].name, r);
			*path = g_ctx[r].c_path;
			*lastdir = g_ctx[r].c_last;
			*lastname = g_ctx[r].c_name;
		}
	}

	return TRUE;
}