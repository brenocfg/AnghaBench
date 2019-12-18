#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_5__ {int /*<<< orphan*/  blocksize; int /*<<< orphan*/  offset; int /*<<< orphan*/  print; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  help_msg_po ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_core_transform_op (TYPE_1__*,char const*,char const) ; 
 int /*<<< orphan*/  r_print_hexdump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void cmd_print_op(RCore *core, const char *input) {
	ut8 *buf;
	if (!input[0])
		return;
	switch (input[1]) {
	case 'a':
	case 's':
	case 'A':
	case 'x':
	case 'r':
	case 'l':
	case 'm':
	case 'd':
	case 'o':
	case '2':
	case '4':
		if (input[2]) {  // parse val from arg
			buf = r_core_transform_op (core, input+3, input[1]);
		} else {  // use clipboard instead of val
			buf = r_core_transform_op (core, NULL, input[1]);
		}
		break;
	case 'n':
		buf = r_core_transform_op (core, "ff", 'x');
		break;
	case '\0':
	case '?':
	default:
		r_core_cmd_help (core, help_msg_po);
		return;
	}
	if (buf) {
		r_print_hexdump(core->print, core->offset, buf,
			core->blocksize, 16, 1, 1);
		free (buf);
	}
}