#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
typedef  int ut32 ;
struct TYPE_7__ {int blocksize_max; int blocksize; int /*<<< orphan*/  num; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int size; } ;
typedef  TYPE_1__ RFlagItem ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  help_msg_b ; 
 int /*<<< orphan*/  r_cons_printf (char*,int,...) ; 
 int /*<<< orphan*/  r_core_block_size (TYPE_2__*,int) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* r_flag_get (int /*<<< orphan*/ ,char const*) ; 
 int r_num_math (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int cmd_bsize(void *data, const char *input) {
	ut64 n;
	RFlagItem *flag;
	RCore *core = (RCore *)data;
	switch (input[0]) {
	case 'm': // "bm"
		n = r_num_math (core->num, input + 1);
		if (n > 1) {
			core->blocksize_max = n;
		} else {
			r_cons_printf ("0x%x\n", (ut32)core->blocksize_max);
		}
		break;
	case '+': // "b+"
		n = r_num_math (core->num, input + 1);
		r_core_block_size (core, core->blocksize + n);
		break;
	case '-': // "b-"
		n = r_num_math (core->num, input + 1);
		r_core_block_size (core, core->blocksize - n);
		break;
	case 'f': // "bf"
		if (input[1] == ' ') {
			flag = r_flag_get (core->flags, input + 2);
			if (flag) {
				r_core_block_size (core, flag->size);
			} else {
				eprintf ("bf: cannot find flag named '%s'\n", input + 2);
			}
		} else {
			eprintf ("Usage: bf [flagname]\n");
		}
		break;
	case 'j': // "bj"
		r_cons_printf ("{\"blocksize\":%d,\"blocksize_limit\":%d}\n", core->blocksize, core->blocksize_max);
		break;
	case '*': // "b*"
		r_cons_printf ("b 0x%x\n", core->blocksize);
		break;
	case '\0': // "b"
		r_cons_printf ("0x%x\n", core->blocksize);
		break;
	case ' ':
		r_core_block_size (core, r_num_math (core->num, input));
		break;
	default:
	case '?': // "b?"
		r_core_cmd_help (core, help_msg_b);
		break;
	}
	return 0;
}