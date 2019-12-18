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
struct TYPE_4__ {int /*<<< orphan*/  autocomplete; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_BRKP ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_DFLT ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_EVAL ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_FCN ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_FILE ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_FLAG ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_FLSP ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_MACR ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_MINS ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_MS ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_PRJT ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_SDB ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_SEEK ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_THME ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_ZIGN ; 
 int /*<<< orphan*/  __foreach (TYPE_1__*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_autocomplete_add (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_core_autocomplete_find (int /*<<< orphan*/ ,char*,int) ; 
 int radare_argc ; 
 char** radare_argv ; 

__attribute__((used)) static void __init_autocomplete_default (RCore* core) {
	const char *fcns[] = {
		"afi", "afcf", "afn", NULL
	};
	const char *seeks[] = {
		"s", NULL
	};
	const char *flags[] = {
		"*", "s", "s+", "b", "f", "fg", "?", "?v", "ad", "bf", "c1", "db", "dbw",
		"f-", "fr", "tf", "/a", "/v", "/r", "/re", "aav", "aep", "aef", "afb",
		"afc", "axg", "axt", "axf", "dcu", "ag", "agfl", "aecu", "aesu", "aeim", NULL
	};
	const char *evals[] = {
		"e", "ee", "et", "e?", "e!", "ev", "evj", NULL
	};
	const char *breaks[] = {
		"db-", "dbc", "dbC", "dbd", "dbe", "dbs", "dbi", "dbte", "dbtd", "dbts", NULL
	};
	const char *files[] = {
		".", "..", ".*", "/F", "/m", "!", "!!", "#!c", "#!v", "#!cpipe", "#!vala",
		"#!rust", "#!zig", "#!pipe", "#!python", "aeli", "arp", "dmd", "drp", "o",
		"idp", "idpi", "L", "obf", "o+", "oc", "r2", "rabin2", "rasm2", "rahash2", "rax2",
		"rafind2", "cd", "on", "op", "wf", "rm", "wF", "wp", "Sd", "Sl", "to", "pm",
		"/m", "zos", "zfd", "zfs", "zfz", "cat", "wta", "wtf", "wxf", "dml", "vi",
		"less", "head", "tail", NULL
	};
	const char *projs[] = {
		"Pc", "Pd", "Pi", "Po", "Ps", "P-", NULL
	};
	const char *mounts[] = {
		"md", "mg", "mo", "ms", "mc", "mi", "mw", NULL
	};
	__foreach (core, flags, R_CORE_AUTOCMPLT_FLAG);
	__foreach (core, seeks, R_CORE_AUTOCMPLT_SEEK);
	__foreach (core, fcns, R_CORE_AUTOCMPLT_FCN);
	__foreach (core, evals, R_CORE_AUTOCMPLT_EVAL);
	__foreach (core, breaks, R_CORE_AUTOCMPLT_BRKP);
	__foreach (core, files, R_CORE_AUTOCMPLT_FILE);
	__foreach (core, projs, R_CORE_AUTOCMPLT_PRJT);
	__foreach (core, mounts, R_CORE_AUTOCMPLT_MS);

	r_core_autocomplete_add (core->autocomplete, "-", R_CORE_AUTOCMPLT_MINS, true);
	r_core_autocomplete_add (core->autocomplete, "zs", R_CORE_AUTOCMPLT_ZIGN, true);
	r_core_autocomplete_add (core->autocomplete, "fs", R_CORE_AUTOCMPLT_FLSP, true);
	r_core_autocomplete_add (
		r_core_autocomplete_add (core->autocomplete, "ls", R_CORE_AUTOCMPLT_DFLT, true),
		"-l", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "eco", R_CORE_AUTOCMPLT_THME, true);
	r_core_autocomplete_add (core->autocomplete, "k", R_CORE_AUTOCMPLT_SDB, true);
	/* macros */
	r_core_autocomplete_add (core->autocomplete, ".(", R_CORE_AUTOCMPLT_MACR, true);
	r_core_autocomplete_add (core->autocomplete, "(-", R_CORE_AUTOCMPLT_MACR, true);
	/* just for hints */
	int i;
	for (i = 0; i < radare_argc && radare_argv[i]; i++) {
		if (!r_core_autocomplete_find (core->autocomplete, radare_argv[i], true)) {
			r_core_autocomplete_add (core->autocomplete, radare_argv[i], R_CORE_AUTOCMPLT_DFLT, true);
		}
	}
}