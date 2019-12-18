#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* print; } ;
struct TYPE_4__ {int /*<<< orphan*/  formats; } ;
typedef  int /*<<< orphan*/  RLineCompletion ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_line_completion_push (int /*<<< orphan*/ *,char*) ; 
 char* r_str_newf (char*,char*,char*,char const*) ; 
 char* r_str_word_get0 (char*,int) ; 
 int r_str_word_set0_stack (char*) ; 
 char* sdb_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static int autocomplete_pfele (RCore *core, RLineCompletion *completion, char *key, char *pfx, int idx, char *ptr) {
	int i, ret = 0;
	int len = strlen (ptr);
	char* fmt = sdb_get (core->print->formats, key, NULL);
	if (fmt) {
		int nargs = r_str_word_set0_stack (fmt);
		if (nargs > 1) {
			for (i = 1; i < nargs; i++) {
				const char *arg = r_str_word_get0 (fmt, i);
				char *p = strchr (arg, '(');
				char *p2 = strchr (arg, ')');
				// remove '(' and ')' from fmt
				if (p && p2) {
					arg = p + 1;
					*p2 = '\0';
				}
				if (!len || !strncmp (ptr, arg, len)) {
					char *s = r_str_newf ("pf%s.%s.%s", pfx, key, arg);
					r_line_completion_push (completion, s);
					free (s);
				}
			}
		}
	}
	free (fmt);
	return ret;
}