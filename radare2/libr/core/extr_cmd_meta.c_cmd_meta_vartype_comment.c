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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  anal; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_META_TYPE_VARTYPE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_Ct ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_meta_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* r_meta_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_meta_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_meta_set_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_num_math (int /*<<< orphan*/ ,char const*) ; 
 char* r_str_trim_ro (char const*) ; 
 int /*<<< orphan*/  r_str_unescape (char*) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int cmd_meta_vartype_comment(RCore *core, const char *input) {
	ut64 addr = core->offset;
	switch (input[1]) {
	case '?': // "Ct?"
		r_core_cmd_help (core, help_msg_Ct);
		break;
	case 0: // "Ct"
		r_meta_list (core->anal, R_META_TYPE_VARTYPE, 0);
		break;
	case ' ': // "Ct <vartype comment> @ addr"
		{
		const char* newcomment = r_str_trim_ro (input + 2);
		char *text, *comment = r_meta_get_string (core->anal, R_META_TYPE_VARTYPE, addr);
		char *nc = strdup (newcomment);
		r_str_unescape (nc);
		if (comment) {
			text = malloc (strlen (comment)+ strlen (newcomment)+2);
			if (text) {
				strcpy (text, comment);
				strcat (text, " ");
				strcat (text, nc);
				r_meta_set_string (core->anal, R_META_TYPE_VARTYPE, addr, text);
				free (comment);
				free (text);
			} else {
				r_sys_perror ("malloc");
			}
		} else {
			r_meta_set_string (core->anal, R_META_TYPE_VARTYPE, addr, nc);
		}
		free (nc);
		}
		break;
	case '.': // "Ct. @ addr"
		{
		ut64 at = input[2]? r_num_math (core->num, input + 2): addr;
		char *comment = r_meta_get_string (
				core->anal, R_META_TYPE_VARTYPE, at);
		if (comment) {
			r_cons_println (comment);
			free (comment);
		}
		}
		break;
	case '-': // "Ct-"
		r_meta_del (core->anal, R_META_TYPE_VARTYPE, core->offset, 1);
		break;
	default:
		r_core_cmd_help (core, help_msg_Ct);
		break;
	}

	return true;
}