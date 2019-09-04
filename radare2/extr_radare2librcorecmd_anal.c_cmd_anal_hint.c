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
typedef  void* ut64 ;
struct TYPE_4__ {void* offset; int /*<<< orphan*/  anal; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_ah ; 
 int /*<<< orphan*/  help_msg_ahi ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  r_anal_hint_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_hint_del (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  r_anal_hint_set_arch (int /*<<< orphan*/ ,void*,char const*) ; 
 int /*<<< orphan*/  r_anal_hint_set_bits (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  r_anal_hint_set_esil (int /*<<< orphan*/ ,void*,char const*) ; 
 int /*<<< orphan*/  r_anal_hint_set_fail (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  r_anal_hint_set_high (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_set_immbase (int /*<<< orphan*/ ,void*,int const) ; 
 int /*<<< orphan*/  r_anal_hint_set_jump (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  r_anal_hint_set_nword (int /*<<< orphan*/ ,void*,char const) ; 
 int /*<<< orphan*/  r_anal_hint_set_opcode (int /*<<< orphan*/ ,void*,char const*) ; 
 int /*<<< orphan*/  r_anal_hint_set_pointer (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  r_anal_hint_set_ret (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  r_anal_hint_set_size (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_anal_hint_set_syntax (int /*<<< orphan*/ ,void*,char const*) ; 
 int /*<<< orphan*/  r_anal_hint_set_type (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  r_anal_hint_unset_arch (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_unset_bits (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_unset_esil (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_unset_fail (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_unset_high (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_unset_jump (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_unset_opcode (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_unset_pointer (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_unset_ret (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_unset_size (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  r_anal_hint_unset_syntax (int /*<<< orphan*/ ,void*) ; 
 int r_anal_optype_from_string (char const*) ; 
 int /*<<< orphan*/  r_core_anal_hint_list (int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  r_core_anal_hint_print (int /*<<< orphan*/ ,void*,char) ; 
 int /*<<< orphan*/  r_core_cmd_help (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* r_num_math (int /*<<< orphan*/ ,char const*) ; 
 char const* r_str_trim_ro (char const*) ; 
 char const* r_str_word_get0 (char*,int) ; 
 int r_str_word_set0 (char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void cmd_anal_hint(RCore *core, const char *input) {
	switch (input[0]) {
	case '?':
		if (input[1]) {
			ut64 addr = r_num_math (core->num, input + 1);
			r_core_anal_hint_print (core->anal, addr, 0);
		} else {
			r_core_cmd_help (core, help_msg_ah);
		}
		break;
	case '.': // "ah."
		r_core_anal_hint_print (core->anal, core->offset, 0);
		break;
	case 'a': // "aha" set arch
		if (input[1]) {
			int i;
			char *ptr = strdup (input + 2);
			i = r_str_word_set0 (ptr);
			if (i == 2) {
				r_num_math (core->num, r_str_word_get0 (ptr, 1));
			}
			r_anal_hint_set_arch (core->anal, core->offset, r_str_word_get0 (ptr, 0));
			free (ptr);
		} else if (input[1] == '-') {
			r_anal_hint_unset_arch (core->anal, core->offset);
		} else {
			eprintf ("Missing argument\n");
		}
		break;
	case 't': // "aht"
		if (input[1] == ' ') {
			const char *arg = r_str_trim_ro (input + 1);
			int type = r_anal_optype_from_string (arg);
			r_anal_hint_set_type (core->anal, core->offset, type);
		} else {
			eprintf ("Usage: aht [type] # can be mov, jmp, call, ...\n");
		}
		break;
	case 'b': // "ahb" set bits
		if (input[1]) {
			char *ptr = strdup (input + 2);
			int bits;
			int i = r_str_word_set0 (ptr);
			if (i == 2) {
				r_num_math (core->num, r_str_word_get0 (ptr, 1));
			}
			bits = r_num_math (core->num, r_str_word_get0 (ptr, 0));
			r_anal_hint_set_bits (core->anal, core->offset, bits);
			free (ptr);
		}  else if (input[1] == '-') {
			r_anal_hint_unset_bits (core->anal, core->offset);
		} else {
			eprintf ("Missing argument\n");
		}
		break;
	case 'i': // "ahi"
		if (input[1] == '?') {
			r_core_cmd_help (core, help_msg_ahi);
		} else if (isdigit (input[1])) {
			r_anal_hint_set_nword (core->anal, core->offset, input[1] - '0');
			input++;
		} else if (input[1] == '-') { // "ahi-"
			r_anal_hint_set_immbase (core->anal, core->offset, 0);
		}
		if (input[1] == ' ') {
			// You can either specify immbase with letters, or numbers
			const int base =
				(input[2] == 's') ? 1 :
				(input[2] == 'b') ? 2 :
				(input[2] == 'p') ? 3 :
				(input[2] == 'o') ? 8 :
				(input[2] == 'd') ? 10 :
				(input[2] == 'h') ? 16 :
				(input[2] == 'i') ? 32 : // ip address
				(input[2] == 'S') ? 80 : // syscall
				(int) r_num_math (core->num, input + 1);
			r_anal_hint_set_immbase (core->anal, core->offset, base);
		} else if (input[1] != '?' && input[1] != '-') {
			eprintf ("|ERROR| Usage: ahi [base]\n");
		}
		break;
	case 'h': // "ahh"
		if (input[1] == '-') {
			r_anal_hint_unset_high (core->anal, core->offset);
		} else if (input[1] == ' ') {
			r_anal_hint_set_high (core->anal, r_num_math (core->num, input + 1));
		} else {
			r_anal_hint_set_high (core->anal, core->offset);
		}
		break;
	case 'c': // "ahc"
		if (input[1] == ' ') {
			r_anal_hint_set_jump (
				core->anal, core->offset,
				r_num_math (core->num, input + 1));
		} else if (input[1] == '-') {
			r_anal_hint_unset_jump (core->anal, core->offset);
		}
		break;
	case 'f': // "ahf"
		if (input[1] == ' ') {
			r_anal_hint_set_fail (
				core->anal, core->offset,
				r_num_math (core->num, input + 1));
		} else if (input[1] == '-') {
			r_anal_hint_unset_fail (core->anal, core->offset);
		}
		break;
	case 's': // "ahs" set size (opcode length)
		if (input[1] == ' ') {
			r_anal_hint_set_size (core->anal, core->offset, atoi (input + 1));
		} else if (input[1] == '-') {
			r_anal_hint_unset_size (core->anal, core->offset);
		} else {
			eprintf ("Usage: ahs 16\n");
		}
		break;
	case 'S': // "ahS" set size (opcode length)
		if (input[1] == ' ') {
			r_anal_hint_set_syntax (core->anal, core->offset, input + 2);
		} else if (input[1] == '-') {
			r_anal_hint_unset_syntax (core->anal, core->offset);
		} else {
			eprintf ("Usage: ahS att\n");
		}
		break;
	case 'o': // "aho" set opcode string
		if (input[1] == ' ') {
			r_anal_hint_set_opcode (core->anal, core->offset, input + 2);
		} else if (input[1] == '-') {
			r_anal_hint_unset_opcode (core->anal, core->offset);
		} else {
			eprintf ("Usage: aho popall\n");
		}
		break;
	case 'e': // "ahe" set ESIL string
		if (input[1] == ' ') {
			r_anal_hint_set_esil (core->anal, core->offset, input + 2);
		} else if (input[1] == '-') {
			r_anal_hint_unset_esil (core->anal, core->offset);
		} else {
			eprintf ("Usage: ahe r0,pc,=\n");
		}
		break;
#if 0
	case 'e': // set endian
		if (input[1] == ' ') {
			r_anal_hint_set_opcode (core->anal, core->offset, atoi (input + 1));
		} else if (input[1] == '-') {
			r_anal_hint_unset_opcode (core->anal, core->offset);
		}
		break;
#endif
	case 'p': // "ahp"
		if (input[1] == ' ') {
			r_anal_hint_set_pointer (core->anal, core->offset, r_num_math (core->num, input + 1));
		} else if (input[1] == '-') { // "ahp-"
			r_anal_hint_unset_pointer (core->anal, core->offset);
		}
		break;
	case 'r': // "ahr"
		if (input[1] == ' ') {
			r_anal_hint_set_ret (core->anal, core->offset, r_num_math (core->num, input + 1));
		} else if (input[1] == '-') { // "ahr-"
			r_anal_hint_unset_ret (core->anal, core->offset);
		}
	case '*': // "ah*"
		if (input[1] == ' ') {
			char *ptr = strdup (r_str_trim_ro (input + 2));
			r_str_word_set0 (ptr);
			ut64 addr = r_num_math (core->num, r_str_word_get0 (ptr, 0));
			r_core_anal_hint_print (core->anal, addr, '*');
		} else {
			r_core_anal_hint_list (core->anal, input[0]);
		}
		break;
	case 'j': // "ahj"
	case '\0': // "ah"
		r_core_anal_hint_list (core->anal, input[0]);
		break;
	case '-': // "ah-"
		if (input[1]) {
			if (input[1] == '*') {
				r_anal_hint_clear (core->anal);
			} else {
				char *ptr = strdup (r_str_trim_ro (input + 1));
				ut64 addr;
				int size = 1;
				int i = r_str_word_set0 (ptr);
				if (i == 2) {
					size = r_num_math (core->num, r_str_word_get0 (ptr, 1));
				}
				const char *a0 = r_str_word_get0 (ptr, 0);
				if (a0 && *a0) {
					addr = r_num_math (core->num, a0);
				} else {
					addr = core->offset;
				}
				r_anal_hint_del (core->anal, addr, size);
				free (ptr);
			}
		} else {
			r_anal_hint_clear (core->anal);
		}
		break;
	}
}