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
struct TYPE_4__ {size_t gl_pathc; char** gl_pathv; scalar_t__ gl_offs; } ;
typedef  TYPE_1__ glob_t ;

/* Variables and functions */
 int GLOB_ERR ; 
 int GLOB_MARK ; 
 size_t GLOB_NOMATCH ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 int /*<<< orphan*/  efree (char*) ; 
 scalar_t__ fpm_conf_load_ini_file (char*) ; 
 size_t glob (char*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ini_filename ; 
 int /*<<< orphan*/  ini_lineno ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static void fpm_conf_ini_parser_include(char *inc, void *arg) /* {{{ */
{
	char *filename;
	int *error = (int *)arg;
#ifdef HAVE_GLOB
	glob_t g;
#endif
	size_t i;

	if (!inc || !arg) return;
	if (*error) return; /* We got already an error. Switch to the end. */
	spprintf(&filename, 0, "%s", ini_filename);

#ifdef HAVE_GLOB
	{
		g.gl_offs = 0;
		if ((i = glob(inc, GLOB_ERR | GLOB_MARK, NULL, &g)) != 0) {
#ifdef GLOB_NOMATCH
			if (i == GLOB_NOMATCH) {
				zlog(ZLOG_WARNING, "Nothing matches the include pattern '%s' from %s at line %d.", inc, filename, ini_lineno);
				efree(filename);
				return;
			}
#endif /* GLOB_NOMATCH */
			zlog(ZLOG_ERROR, "Unable to globalize '%s' (ret=%zd) from %s at line %d.", inc, i, filename, ini_lineno);
			*error = 1;
			efree(filename);
			return;
		}

		for (i = 0; i < g.gl_pathc; i++) {
			int len = strlen(g.gl_pathv[i]);
			if (len < 1) continue;
			if (g.gl_pathv[i][len - 1] == '/') continue; /* don't parse directories */
			if (0 > fpm_conf_load_ini_file(g.gl_pathv[i])) {
				zlog(ZLOG_ERROR, "Unable to include %s from %s at line %d", g.gl_pathv[i], filename, ini_lineno);
				*error = 1;
				efree(filename);
				return;
			}
		}
		globfree(&g);
	}
#else /* HAVE_GLOB */
	if (0 > fpm_conf_load_ini_file(inc)) {
		zlog(ZLOG_ERROR, "Unable to include %s from %s at line %d", inc, filename, ini_lineno);
		*error = 1;
		efree(filename);
		return;
	}
#endif /* HAVE_GLOB */

	efree(filename);
}