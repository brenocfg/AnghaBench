#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  meta_spaces; } ;
struct TYPE_14__ {TYPE_2__* anal; int /*<<< orphan*/  offset; int /*<<< orphan*/  num; } ;
typedef  int /*<<< orphan*/  RSpaces ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  RAnalFunction ;

/* Variables and functions */
 int R_ANAL_FCN_TYPE_FCN ; 
 int R_ANAL_FCN_TYPE_SYM ; 
 int /*<<< orphan*/  R_META_TYPE_ANY ; 
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  cmd_meta_comment (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  cmd_meta_lineinfo (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  cmd_meta_others (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  cmd_meta_vartype_comment (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  help_msg_C ; 
 int /*<<< orphan*/  help_msg_CS ; 
 int /*<<< orphan*/ * r_anal_get_fcn_in (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_anal_str_to_fcn (TYPE_2__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_comment_vars (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_meta_cleanup (TYPE_2__*,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_meta_del (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_meta_list (TYPE_2__*,int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  r_meta_list_offset (TYPE_2__*,int /*<<< orphan*/ ,char const) ; 
 int r_num_math (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_spaces_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_spaces_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_spaces_rename (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_spaces_set (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_spaces_unset (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  spaces_list (int /*<<< orphan*/ *,char const) ; 

__attribute__((used)) static int cmd_meta(void *data, const char *input) {
	RCore *core = (RCore*)data;
	RAnalFunction *f;
	RSpaces *ms;
	int i;

	switch (*input) {
	case 'v': // "Cv"
		r_comment_vars (core, input + 1);
		break;
	case '\0': // "C"
		r_meta_list (core->anal, R_META_TYPE_ANY, 0);
		break;
	case 'j': // "Cj"
	case '*': { // "C*"
		if (!input[0] || input[1] == '.') {
			r_meta_list_offset (core->anal, core->offset, *input);
		} else {
			r_meta_list (core->anal, R_META_TYPE_ANY, *input);
		}
		break;
	}
	case '.': { // "C."
		r_meta_list_offset (core->anal, core->offset, 0);
		break;
	}
	case 'L': // "CL"
		cmd_meta_lineinfo (core, input + 1);
		break;
	case 'C': // "CC"
		cmd_meta_comment (core, input);
		break;
	case 't': // "Ct" type analysis commnets
		cmd_meta_vartype_comment (core, input);
		break;
	case 'r': // "Cr" run command
	case 'h': // "Ch" comment
	case 's': // "Cs" string
	case 'z': // "Cz" zero-terminated string
	case 'd': // "Cd" data
	case 'm': // "Cm" magic
	case 'f': // "Cf" formatted
		cmd_meta_others (core, input);
		break;
	case '-': // "C-"
		if (input[1] != '*') {
			i = input[1] ? r_num_math (core->num, input + (input[1] == ' ' ? 2 : 1)) : 1;
			r_meta_del (core->anal, R_META_TYPE_ANY, core->offset, i);
		} else r_meta_cleanup (core->anal, 0LL, UT64_MAX);
		break;
	case '?': // "C?"
		r_core_cmd_help (core, help_msg_C);
		break;
	case 'F': // "CF"
		f = r_anal_get_fcn_in (core->anal, core->offset,
			R_ANAL_FCN_TYPE_FCN|R_ANAL_FCN_TYPE_SYM);
		if (f) {
			r_anal_str_to_fcn (core->anal, f, input + 2);
		} else {
			eprintf ("Cannot find function here\n");
		}
		break;
	case 'S': // "CS"
		ms = &core->anal->meta_spaces;
		/** copypasta from `fs`.. this must be refactorized to be shared */
		switch (input[1]) {
		case '?': // "CS?"
			r_core_cmd_help (core, help_msg_CS);
			break;
		case '+': // "CS+"
			r_spaces_push (ms, input + 2);
			break;
		case 'r': // "CSr"
			if (input[2] == ' ') {
				r_spaces_rename (ms, NULL, input+2);
			} else {
				eprintf ("Usage: CSr [newname]\n");
			}
			break;
		case '-': // "CS-"
			if (input[2]) {
				if (input[2]=='*') {
					r_spaces_unset (ms, NULL);
				} else {
					r_spaces_unset (ms, input+2);
				}
			} else {
				r_spaces_pop (ms);
			}
			break;
		case 'j': // "CSj"
		case '\0': // "CS"
		case '*': // "CS*"
			spaces_list (ms, input[1]);
			break;
		case ' ': // "CS "
			r_spaces_set (ms, input + 2);
			break;
		default:
			spaces_list (ms, 0);
			break;
		}
		break;
	}
	return true;
}