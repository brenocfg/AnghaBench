#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut32 ;
struct r_magic_entry {int dummy; } ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_6__ {char const* file; int line; } ;
typedef  TYPE_1__ RMagic ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_error (TYPE_1__*,scalar_t__,char*,char const*) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mime_marker ; 
 size_t mime_marker_len ; 
 scalar_t__ parse (TYPE_1__*,struct r_magic_entry**,int /*<<< orphan*/ *,char*,size_t,int) ; 
 scalar_t__ parse_mime (TYPE_1__*,struct r_magic_entry**,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * r_sandbox_fopen (char const*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void load_1(RMagic *ms, int action, const char *file, int *errs, struct r_magic_entry **marray, ut32 *marraycount) {
	char line[BUFSIZ];
	size_t lineno = 0;
	FILE *f = r_sandbox_fopen (ms->file = file, "r");
	if (!f) {
		if (errno != ENOENT) {
			file_error (ms, errno, "cannot read magic file `%s'", file);
		}
		(*errs)++;
	} else {
		/* read and parse this file */
		for (ms->line = 1; fgets (line, sizeof (line), f) != NULL; ms->line++) {
			size_t len = strlen (line);
			if (len == 0) { /* null line, garbage, etc */
				continue;
			}
			if (line[len - 1] == '\n') {
				lineno++;
				line[len - 1] = '\0'; /* delete newline */
			}
			if (line[0] == '\0') { /* empty, do not parse */
				continue;
			}
			if (line[0] == '#') { /* comment, do not parse */
				continue;
			}
			if (len > mime_marker_len &&
			    memcmp (line, mime_marker, mime_marker_len) == 0) {
				/* MIME type */
				if (parse_mime (ms, marray, marraycount,
					    line + mime_marker_len) != 0) {
					(*errs)++;
				}
				continue;
			}
			if (parse (ms, marray, marraycount, line, lineno, action) != 0) {
				(*errs)++;
			}
		}
		fclose (f);
	}
}