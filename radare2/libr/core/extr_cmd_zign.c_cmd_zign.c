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
struct TYPE_4__ {int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int cmdAdd (void*,char const*) ; 
 int cmdCheck (void*,char const*) ; 
 int cmdCompare (void*,char const*) ; 
 int cmdFlirt (void*,char const*) ; 
 int cmdInfo (void*,char const*) ; 
 int cmdOpen (void*,char const*) ; 
 int cmdSearch (void*,char const*) ; 
 int cmdSpace (void*,char const*) ; 
 int /*<<< orphan*/  help_msg_z ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sign_delete (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_sign_list (int /*<<< orphan*/ ,char const) ; 

__attribute__((used)) static int cmd_zign(void *data, const char *input) {
	RCore *core = (RCore *) data;

	switch (*input) {
	case '\0':
	case '*':
	case 'q':
	case 'j':
		r_sign_list (core->anal, input[0]);
		break;
	case 'k':
		r_core_cmd0 (core, "k anal/zigns/*");
		break;
	case '-':
		r_sign_delete (core->anal, input + 1);
		break;
	case '.': // "z."
		return cmdCheck (data, input + 1);
	case 'o': // "zo"
		return cmdOpen (data, input + 1);
	case 'g': // "zg"
		return cmdAdd (data, "F");
	case 'a': // "za"
		return cmdAdd (data, input + 1);
	case 'f': // "zf"
		return cmdFlirt (data, input + 1);
	case '/': // "z/"
		return cmdSearch (data, input + 1);
	case 'c': // "zc"
		return cmdCompare (data, input + 1);
	case 's': // "zs"
		return cmdSpace (data, input + 1);
	case 'i': // "zi"
		return cmdInfo (data, input + 1);
	case '?': // "z?"
		r_core_cmd_help (core, help_msg_z);
		break;
	default:
		r_core_cmd_help (core, help_msg_z);
		return false;
	}

	return true;
}