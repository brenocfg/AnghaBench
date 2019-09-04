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
struct TYPE_3__ {int /*<<< orphan*/  autocomplete; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  RCoreAutocomplete ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_BRKP ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_DFLT ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_EVAL ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_FCN ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_FILE ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_FLAG ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_FLSP ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_MACR ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_MINS ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_PRJT ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_THME ; 
 int /*<<< orphan*/  R_CORE_AUTOCMPLT_ZIGN ; 
 int /*<<< orphan*/  R_NEW0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_autocomplete_add (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_core_autocomplete_find (int /*<<< orphan*/ ,char*,int) ; 
 int radare_argc ; 
 char** radare_argv ; 

__attribute__((used)) static void init_autocomplete (RCore* core) {
	core->autocomplete = R_NEW0 (RCoreAutocomplete);
	/* flags */
	r_core_autocomplete_add (core->autocomplete, "*", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "s", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "s+", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "b", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "f", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "?", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "?v", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "ad", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "bf", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "c1", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "db", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "dbw", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "f-", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "fr", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "tf", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "/a", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "/v", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "/r", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "/re", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "aav", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "aep", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "aef", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "afb", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "afc", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "axg", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "axt", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "axf", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "dcu", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "ag", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "agfl", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "aecu", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "aesu", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "aeim", R_CORE_AUTOCMPLT_FLAG, true);
	r_core_autocomplete_add (core->autocomplete, "afi", R_CORE_AUTOCMPLT_FCN, true);
	r_core_autocomplete_add (core->autocomplete, "afcf", R_CORE_AUTOCMPLT_FCN, true);
	/* evars */
	r_core_autocomplete_add (core->autocomplete, "e", R_CORE_AUTOCMPLT_EVAL, true);
	r_core_autocomplete_add (core->autocomplete, "ee", R_CORE_AUTOCMPLT_EVAL, true);
	r_core_autocomplete_add (core->autocomplete, "et", R_CORE_AUTOCMPLT_EVAL, true);
	r_core_autocomplete_add (core->autocomplete, "e?", R_CORE_AUTOCMPLT_EVAL, true);
	r_core_autocomplete_add (core->autocomplete, "e!", R_CORE_AUTOCMPLT_EVAL, true);
	r_core_autocomplete_add (core->autocomplete, "ev", R_CORE_AUTOCMPLT_EVAL, true);
	r_core_autocomplete_add (core->autocomplete, "evj", R_CORE_AUTOCMPLT_EVAL, true);
	/* cfg.editor */
	r_core_autocomplete_add (core->autocomplete, "-", R_CORE_AUTOCMPLT_MINS, true);
	/* breakpoints */
	r_core_autocomplete_add (core->autocomplete, "db-", R_CORE_AUTOCMPLT_BRKP, true);
	r_core_autocomplete_add (core->autocomplete, "dbc", R_CORE_AUTOCMPLT_BRKP, true);
	r_core_autocomplete_add (core->autocomplete, "dbC", R_CORE_AUTOCMPLT_BRKP, true);
	r_core_autocomplete_add (core->autocomplete, "dbd", R_CORE_AUTOCMPLT_BRKP, true);
	r_core_autocomplete_add (core->autocomplete, "dbe", R_CORE_AUTOCMPLT_BRKP, true);
	r_core_autocomplete_add (core->autocomplete, "dbs", R_CORE_AUTOCMPLT_BRKP, true);
	r_core_autocomplete_add (core->autocomplete, "dbi", R_CORE_AUTOCMPLT_BRKP, true);
	r_core_autocomplete_add (core->autocomplete, "dbte", R_CORE_AUTOCMPLT_BRKP, true);
	r_core_autocomplete_add (core->autocomplete, "dbtd", R_CORE_AUTOCMPLT_BRKP, true);
	r_core_autocomplete_add (core->autocomplete, "dbts", R_CORE_AUTOCMPLT_BRKP, true);
	/* Project */
	r_core_autocomplete_add (core->autocomplete, "Pc", R_CORE_AUTOCMPLT_PRJT, true);
	r_core_autocomplete_add (core->autocomplete, "Pd", R_CORE_AUTOCMPLT_PRJT, true);
	r_core_autocomplete_add (core->autocomplete, "Pi", R_CORE_AUTOCMPLT_PRJT, true);
	r_core_autocomplete_add (core->autocomplete, "Po", R_CORE_AUTOCMPLT_PRJT, true);
	r_core_autocomplete_add (core->autocomplete, "Ps", R_CORE_AUTOCMPLT_PRJT, true);
	r_core_autocomplete_add (core->autocomplete, "P-", R_CORE_AUTOCMPLT_PRJT, true);
	/* zignatures */
	r_core_autocomplete_add (core->autocomplete, "zs", R_CORE_AUTOCMPLT_ZIGN, true);
	/* flag spaces */
	r_core_autocomplete_add (core->autocomplete, "fs", R_CORE_AUTOCMPLT_FLSP, true);
	/* file path */
	r_core_autocomplete_add (core->autocomplete, ".", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "..", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, ".*", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "/F", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "/m", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "!", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "!!", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "#!c", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "#!cpipe", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "#!vala", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "#!rust", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "#!zig", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "#!pipe", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "#!python", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "aeli", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "arp", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "cf", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "dg", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "dmd", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "drp", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "o", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "idp", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "idpi", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "L", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "obf", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "o+", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "oc", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "r2", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "rabin2", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "rasm2", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "rahash2", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "rax2", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "rafind2", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "cd", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "on", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "op", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "wf", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "rm", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "wF", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "wp", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "Sd", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "Sl", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "to", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "pm", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "/m", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "zos", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "zfd", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "zfs", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "zfz", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "cat", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "wta", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "wtf", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "wxf", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "dml", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "vim", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (core->autocomplete, "less", R_CORE_AUTOCMPLT_FILE, true);
	r_core_autocomplete_add (r_core_autocomplete_add (core->autocomplete, "ls", R_CORE_AUTOCMPLT_DFLT, true), "-l", R_CORE_AUTOCMPLT_FILE, true);
	/* macros */
	r_core_autocomplete_add (core->autocomplete, ".(", R_CORE_AUTOCMPLT_MACR, true);
	r_core_autocomplete_add (core->autocomplete, "(-", R_CORE_AUTOCMPLT_MACR, true);
	/* theme */
	r_core_autocomplete_add (core->autocomplete, "eco", R_CORE_AUTOCMPLT_THME, true);
	/* just for hints */
	int i;
	for (i = 0; i < radare_argc && radare_argv[i]; i++) {
		if (!r_core_autocomplete_find (core->autocomplete, radare_argv[i], true)) {
			r_core_autocomplete_add (core->autocomplete, radare_argv[i], R_CORE_AUTOCMPLT_DFLT, true);
		}
	}
}