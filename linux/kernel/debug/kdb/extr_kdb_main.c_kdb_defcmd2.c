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
struct defcmd_set {char** command; int count; int usable; int /*<<< orphan*/  help; int /*<<< orphan*/  usage; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KDB ; 
 int /*<<< orphan*/  KDB_ENABLE_ALWAYS_SAFE ; 
 int KDB_NOTIMP ; 
 int defcmd_in_progress ; 
 struct defcmd_set* defcmd_set ; 
 int defcmd_set_count ; 
 char** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdb_exec_defcmd ; 
 int /*<<< orphan*/  kdb_printf (char*,char const*) ; 
 int /*<<< orphan*/  kdb_register_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kdb_strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char**) ; 
 int /*<<< orphan*/  memcpy (char**,char**,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int kdb_defcmd2(const char *cmdstr, const char *argv0)
{
	struct defcmd_set *s = defcmd_set + defcmd_set_count - 1;
	char **save_command = s->command;
	if (strcmp(argv0, "endefcmd") == 0) {
		defcmd_in_progress = false;
		if (!s->count)
			s->usable = false;
		if (s->usable)
			/* macros are always safe because when executed each
			 * internal command re-enters kdb_parse() and is
			 * safety checked individually.
			 */
			kdb_register_flags(s->name, kdb_exec_defcmd, s->usage,
					   s->help, 0,
					   KDB_ENABLE_ALWAYS_SAFE);
		return 0;
	}
	if (!s->usable)
		return KDB_NOTIMP;
	s->command = kcalloc(s->count + 1, sizeof(*(s->command)), GFP_KDB);
	if (!s->command) {
		kdb_printf("Could not allocate new kdb_defcmd table for %s\n",
			   cmdstr);
		s->usable = false;
		return KDB_NOTIMP;
	}
	memcpy(s->command, save_command, s->count * sizeof(*(s->command)));
	s->command[s->count++] = kdb_strdup(cmdstr, GFP_KDB);
	kfree(save_command);
	return 0;
}