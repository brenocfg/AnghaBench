#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut8 ;
struct TYPE_28__ {int /*<<< orphan*/  help_msg; struct TYPE_28__** sub; } ;
struct TYPE_27__ {TYPE_5__ root_cmd_descriptor; int /*<<< orphan*/  config; TYPE_3__* autocomplete; } ;
struct TYPE_26__ {size_t length; scalar_t__ type; int n_subcmds; TYPE_1__** subcmds; } ;
struct TYPE_25__ {char* data; size_t length; } ;
struct TYPE_24__ {int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  RLineCompletion ;
typedef  TYPE_2__ RLineBuffer ;
typedef  TYPE_3__ RCoreAutocomplete ;
typedef  TYPE_4__ RCore ;
typedef  TYPE_5__ RCmdDescriptor ;

/* Variables and functions */
 size_t R_ARRAY_SIZE (TYPE_5__**) ; 
#define  R_CORE_AUTOCMPLT_BRKP 142 
#define  R_CORE_AUTOCMPLT_EVAL 141 
#define  R_CORE_AUTOCMPLT_FCN 140 
#define  R_CORE_AUTOCMPLT_FILE 139 
#define  R_CORE_AUTOCMPLT_FLAG 138 
#define  R_CORE_AUTOCMPLT_FLSP 137 
#define  R_CORE_AUTOCMPLT_MACR 136 
#define  R_CORE_AUTOCMPLT_MINS 135 
#define  R_CORE_AUTOCMPLT_MS 134 
#define  R_CORE_AUTOCMPLT_OPTN 133 
#define  R_CORE_AUTOCMPLT_PRJT 132 
#define  R_CORE_AUTOCMPLT_SDB 131 
#define  R_CORE_AUTOCMPLT_SEEK 130 
#define  R_CORE_AUTOCMPLT_THME 129 
#define  R_CORE_AUTOCMPLT_ZIGN 128 
 int /*<<< orphan*/  autocomplete_breakpoints (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_evals (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_flags (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_flagspaces (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_functions (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_macro (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_minus (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_ms_file (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_project (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_sdb (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_theme (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  autocomplete_zignatures (TYPE_4__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 TYPE_3__* r_core_autocomplete_find (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_line_completion_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_line_completion_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* r_str_trim_ro (char const*) ; 
 char* r_str_trim_wp (char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool find_autocomplete(RCore *core, RLineCompletion *completion, RLineBuffer *buf) {
	RCoreAutocomplete* child = NULL;
	RCoreAutocomplete* parent = core->autocomplete;
	const char* p = buf->data;
	if (!*p) {
		return false;
	}
	char arg[256];
	arg[0] = 0;
	while (*p) {
		const char* e = r_str_trim_wp (p);
		if (!e || (e - p) >= 256 || e == p) {
			return false;
		}
		memcpy (arg, p, e - p);
		arg[e - p] = 0;
		child = r_core_autocomplete_find (parent, arg, false);
		if (child && child->length < buf->length && p[child->length] == ' ') {
			// if is spaced then i can provide the
			// next subtree as suggestion..
			p = r_str_trim_ro (p + child->length);
			if (child->type == R_CORE_AUTOCMPLT_OPTN) {
				continue;
			}
			parent = child;
		} else {
			break;
		}
	}
	int i;
	/* if something went wrong this will prevent bad behavior */
	r_line_completion_clear (completion);
	switch (parent->type) {
	case R_CORE_AUTOCMPLT_SEEK:
		autocomplete_functions (core, completion, p);
	case R_CORE_AUTOCMPLT_FLAG:
		autocomplete_flags (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_FLSP:
		autocomplete_flagspaces (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_FCN:
		autocomplete_functions (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_ZIGN:
		autocomplete_zignatures (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_EVAL:
		autocomplete_evals (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_PRJT:
		autocomplete_project (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_MINS:
		autocomplete_minus (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_BRKP:
		autocomplete_breakpoints (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_MACR:
		autocomplete_macro (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_MS:
		autocomplete_ms_file(core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_FILE:
		autocomplete_file (completion, p);
		break;
	case R_CORE_AUTOCMPLT_THME:
		autocomplete_theme (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_SDB:
		autocomplete_sdb (core, completion, p);
		break;
	case R_CORE_AUTOCMPLT_OPTN:
		// handled before
		break;
	default:
		if (r_config_get_i (core->config, "cfg.newtab")) {
			RCmdDescriptor *desc = &core->root_cmd_descriptor;
			for (i = 0; arg[i] && desc; i++) {
				ut8 c = arg[i];
				desc = c < R_ARRAY_SIZE (desc->sub) ? desc->sub[c] : NULL;
			}
			if (desc && desc->help_msg) {
				r_core_cmd_help (core, desc->help_msg);
				r_cons_flush ();
				return true;
			}
			// fallback to command listing
		}
		int length = strlen (arg);
		for (i = 0; i < parent->n_subcmds; i++) {
			if (!strncmp (arg, parent->subcmds[i]->cmd, length)) {
				r_line_completion_push (completion, parent->subcmds[i]->cmd);
			}
		}
		break;
	}
	return true;
}