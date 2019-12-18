#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut32 ;
struct TYPE_7__ {int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,int) ;scalar_t__ name; } ;
struct TYPE_6__ {int blocksize; int /*<<< orphan*/  block; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  algolist (int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 TYPE_4__* hash_handlers ; 
 int /*<<< orphan*/  r_core_block_read (TYPE_1__*) ; 
 int /*<<< orphan*/  r_core_block_size (TYPE_1__*,int) ; 
 int r_num_math (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  r_str_ccmp (scalar_t__,char const*,char) ; 
 char* r_str_trim_ro (char const*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool cmd_print_ph(RCore *core, const char *input) {
	char algo[128];
	ut32 osize = 0, len = core->blocksize;
	const char *ptr;
	int pos = 0, handled_cmd = false;

	if (!*input || *input == '?') {
		algolist (1);
		return true;
	}
	if (*input == '=') {
		algolist (0);
		return true;
	}
	input = r_str_trim_ro (input);
	ptr = strchr (input, ' ');
	sscanf (input, "%31s", algo);
	if (ptr && ptr[1]) { // && r_num_is_valid_input (core->num, ptr + 1)) {
		int nlen = r_num_math (core->num, ptr + 1);
		if (nlen > 0) {
			len = nlen;
		}
		osize = core->blocksize;
		if (nlen > core->blocksize) {
			r_core_block_size (core, nlen);
			if (nlen != core->blocksize) {
				eprintf ("Invalid block size\n");
				r_core_block_size (core, osize);
				return false;
			}
			r_core_block_read (core);
		}
	} else if (!ptr || !*(ptr + 1)) {
		osize = len;
	}
	/* TODO: Simplify this spaguetti monster */
	while (osize > 0 && hash_handlers[pos].name) {
		if (!r_str_ccmp (hash_handlers[pos].name, input, ' ')) {
			hash_handlers[pos].handler (core->block, len);
			handled_cmd = true;
			break;
		}
		pos++;
	}
	if (osize) {
		r_core_block_size (core, osize);
	}
	return handled_cmd;
}