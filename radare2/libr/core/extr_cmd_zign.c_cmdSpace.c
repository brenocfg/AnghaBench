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
struct TYPE_5__ {TYPE_1__* anal; } ;
struct TYPE_4__ {int /*<<< orphan*/  zign_spaces; } ;
typedef  int /*<<< orphan*/  RSpaces ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  help_msg_zs ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_spaces_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_spaces_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_spaces_rename (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_spaces_set (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_spaces_unset (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  spaces_list (int /*<<< orphan*/ *,char const) ; 

__attribute__((used)) static int cmdSpace(void *data, const char *input) {
	RCore *core = (RCore *) data;
	RSpaces *zs = &core->anal->zign_spaces;

	switch (*input) {
	case '+':
		if (!input[1]) {
			eprintf ("usage: zs+zignspace\n");
			return false;
		}
		r_spaces_push (zs, input + 1);
		break;
	case 'r':
		if (input[1] != ' ' || !input[2]) {
			eprintf ("usage: zsr newname\n");
			return false;
		}
		r_spaces_rename (zs, NULL, input + 2);
		break;
	case '-':
		if (input[1] == '\x00') {
			r_spaces_pop (zs);
		} else if (input[1] == '*') {
			r_spaces_unset (zs, NULL);
		} else {
			r_spaces_unset (zs, input + 1);
		}
		break;
	case 'j':
	case '*':
	case '\0':
		spaces_list (zs, input[0]);
		break;
	case ' ':
		if (!input[1]) {
			eprintf ("usage: zs zignspace\n");
			return false;
		}
		r_spaces_set (zs, input + 1);
		break;
	case '?':
		r_core_cmd_help (core, help_msg_zs);
		break;
	default:
		eprintf ("usage: zs[+-*] [namespace]\n");
		return false;
	}

	return true;
}