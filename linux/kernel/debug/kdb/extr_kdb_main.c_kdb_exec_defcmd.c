#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct defcmd_set {int count; int /*<<< orphan*/ * command; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int KDB_ARGCOUNT ; 
 int KDB_NOTIMP ; 
 struct defcmd_set* defcmd_set ; 
 int defcmd_set_count ; 
 int kdb_parse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdb_printf (char*,char const*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int kdb_exec_defcmd(int argc, const char **argv)
{
	int i, ret;
	struct defcmd_set *s;
	if (argc != 0)
		return KDB_ARGCOUNT;
	for (s = defcmd_set, i = 0; i < defcmd_set_count; ++i, ++s) {
		if (strcmp(s->name, argv[0]) == 0)
			break;
	}
	if (i == defcmd_set_count) {
		kdb_printf("kdb_exec_defcmd: could not find commands for %s\n",
			   argv[0]);
		return KDB_NOTIMP;
	}
	for (i = 0; i < s->count; ++i) {
		/* Recursive use of kdb_parse, do not use argv after
		 * this point */
		argv = NULL;
		kdb_printf("[%s]kdb> %s\n", s->name, s->command[i]);
		ret = kdb_parse(s->command[i]);
		if (ret)
			return ret;
	}
	return 0;
}