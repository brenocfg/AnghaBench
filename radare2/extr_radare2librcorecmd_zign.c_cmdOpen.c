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
struct TYPE_3__ {int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  help_msg_zo ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int r_sign_load (int /*<<< orphan*/ ,char const*) ; 
 int r_sign_load_gz (int /*<<< orphan*/ ,char const*) ; 
 int r_sign_save (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int cmdOpen(void *data, const char *input) {
	RCore *core = (RCore *) data;

	switch (*input) {
	case ' ':
		if (input[1]) {
			return r_sign_load (core->anal, input + 1);
		}
		eprintf ("usage: zo filename\n");
		return false;
	case 's':
		if (input[1] == ' ' && input[2]) {
			return r_sign_save (core->anal, input + 2);
		}
		eprintf ("usage: zos filename\n");
		return false;
	case 'z':
		if (input[1] == ' ' && input[2]) {
			return r_sign_load_gz (core->anal, input + 2);
		}
		eprintf ("usage: zoz filename\n");
		return false;
	case '?':
		r_core_cmd_help (core, help_msg_zo);
		break;
	default:
		eprintf ("usage: zo[zs] filename\n");
		return false;
	}

	return true;
}