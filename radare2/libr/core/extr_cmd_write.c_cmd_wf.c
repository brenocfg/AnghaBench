#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* ut64 ;
struct TYPE_8__ {int blocksize; int /*<<< orphan*/  offset; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int cmd_wff (TYPE_1__*,char const*) ; 
 int cmd_wfs (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_wf ; 
 int /*<<< orphan*/  ioMemcpy (TYPE_1__*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  r_core_block_read (TYPE_1__*) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* r_num_math (int /*<<< orphan*/ ,char*) ; 
 char* r_str_trim_dup (char const*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static bool cmd_wf(RCore *core, const char *input) {
	if (!core || !*input) {
		return false;
	}
	if (input[1] == '?') {
		eprintf ("Usage: wf [file] ([size] ([offset]))\n");
		r_core_cmd_help (core, help_msg_wf);
		return false;
	}
	if (input[1] == 's') { // "wfs"
		return cmd_wfs (core, input + 1);
	}
	if (input[1] == 'f') { // "wff"
		return cmd_wff (core, input + 1);
	}
	char *args = r_str_trim_dup (input + 1);
	char *arg = strchr (args, ' ');
	int len = core->blocksize;
	if (arg) {
		*arg++ = 0;
		len = r_num_math (core->num, arg);
	}
	ut64 addr = r_num_math (core->num, args);
	ioMemcpy (core, core->offset, addr, len);
	free (args);
	r_core_block_read (core);
	return true;
}