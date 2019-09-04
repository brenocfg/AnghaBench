#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  r_str_replace_char (char*,char,char) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int replace(int argc, const char *argv[], char *newstr) {
#define MAXPSEUDOOPS 10
	int i, j, k, d;
	char ch;
	struct {
		int narg;
		char *op;
		char *str;
		int args[MAXPSEUDOOPS];
	} ops[] = {
		{ 0, "abs", "# = abs(#)", { 1, 1 } },
		{ 0, "adc", "# = # + #", { 1, 2, 3 } },
		{ 3, "add", "# = # + #", { 1, 2, 3 } },
		{ 2, "add", "# += #", { 1, 2 } },
		{ 2, "adds", "# += #", { 1, 2 } },
		{ 3, "adds", "# = # + #", { 1, 2, 3 } },
		{ 3, "addw", "# = # + #", { 1, 2, 3 } },
		{ 3, "add.w", "# = # + #", { 1, 2, 3 } },
		{ 0, "adf", "# = # + #", { 1, 2, 3 } },
		{ 0, "adrp", "# = #", { 1, 2 } },
		{ 0, "adr", "# = #", { 1, 2 } },
		{ 0, "and", "# = # & #", { 1, 2, 3 } },
		{ 0, "ands", "# &= #", { 1, 2 } },
		{ 0, "asls", "# = # << #", { 1, 2, 3 } },
		{ 0, "asl", "# = # << #", { 1, 2, 3 } },
		{ 0, "asrs", "# = # >> #", { 1, 2, 3 } },
		{ 0, "asr", "# = # >> #", { 1, 2, 3 } },
		{ 0, "b", "jmp #", { 1 } },
		{ 0, "cbz", "if !# jmp #", { 1, 2 } },
		{ 0, "cbnz", "if # jmp #", { 1, 2 } },
		{ 0, "b.w", "jmp #", { 1 } },
		{ 0, "b.gt", "jmp ifgt #", { 1 } },
		{ 0, "b.le", "jmp ifle #", { 1 } },
		{ 0, "beq lr", "ifeq ret", { 0 } },
		{ 0, "beq", "je #", { 1 } },
		{ 0, "call", "#()", { 1 } },
		{ 0, "bl", "#()", { 1 } },
		{ 0, "blx", "#()", { 1 } },
		{ 0, "bx lr", "ret", { 0 } },
		{ 0, "bxeq", "je #", { 1 } },
		{ 0, "cmf", "if (# == #)", { 1, 2 } },
		{ 0, "cmn", "if (# != #)", { 1, 2 } },
		{ 0, "cmp", "if (# == #)", { 1, 2 } },
		{ 0, "fcmp", "if (# == #)", { 1, 2 } },
		{ 0, "tst", "if (# == #)", { 1, 2 } },
		{ 0, "dvf", "# = # / #", { 1, 2, 3 } },
		{ 0, "eor", "# = # ^ #", { 1, 2, 3 } },
		{ 0, "fdv", "# = # / #", { 1, 2, 3 } },
		{ 0, "fml", "# = # * #", { 1, 2, 3 } },
		{ 2, "ldr", "# = #", { 1, 2 } },
		{ 2, "ldrh", "# = (word)#", { 1, 2 } },
		{ 2, "ldrb", "# = (byte) #", { 1, 2 } },
		{ 2, "ldrsb", "# = (byte) #", { 1, 2 } },
		{ 2, "ldr.w", "# = #", { 1, 2 } },
		{ 2, "ldrsw", "# = #", { 1, 2 } },
		{ 3, "ldr", "# = # + #", { 1, 2, 3 } },
		{ 3, "ldrb", "# = (byte) # + #", { 1, 2, 3 } },
		{ 3, "ldrsb", "# = (byte) # + #", { 1, 2, 3 } },
		{ 3, "ldr.w", "# = # + #", { 1, 2, 3 } },
		{ 3, "ldrsw", "# = # + #", { 1, 2, 3 } },
		{ 0, "lsl", "# = # << #", { 1, 2, 3 } },
		{ 0, "lsr", "# = # >> #", { 1, 2, 3 } },
		{ 0, "mov", "# = #", { 1, 2 } },
		{ 0, "fmov", "# = #", { 1, 2 } },
		{ 0, "mvn", "# = ~#", { 1, 2 } },
		{ 0, "movz", "# = #", { 1, 2 } },
		{ 0, "movk", "# = #", { 1, 2 } },
		{ 0, "movn", "# = #", { 1, 2 } },
		{ 0, "neg", "# = !#", { 1, 2 } },
		{ 0, "sxtw", "# = #", { 1, 2 } },
		{ 0, "stur", "# = #", { 2, 1 } },
		{ 0, "stp", "# = (#, 2)", { 3, 1 } },
		{ 0, "ldp", "(#, 2) = 3", { 1 } },
		{ 0, "vmov.i32", "# = #", { 1, 2 } },
		{ 0, "muf", "# = # * #", { 1, 2, 3 } },
		{ 0, "mul", "# = # * #", { 1, 2, 3 } },
		{ 0, "fmul", "# = # * #", { 1, 2, 3 } },
		{ 0, "muls", "# = # * #", { 1, 2, 3 } },
		{ 0, "div", "# = # / #", { 1, 2, 3 } },
		{ 0, "fdiv", "# = # / #", { 1, 2, 3 } },
		{ 0, "udiv", "# = (unsigned) # / #", { 1, 2, 3 } },
		{ 0, "orr", "# = # | #", { 1, 2, 3 } },
		{ 0, "rmf", "# = # % #", { 1, 2, 3 } },
		{ 0, "bge", "(>=) goto #", { 1 } },
		{ 0, "sbc", "# = # - #", { 1, 2, 3 } },
		{ 0, "sqt", "# = sqrt(#)", { 1, 2 } },
		{ 0, "lsrs", "# = # >> #", { 1, 2, 3 } },
		{ 0, "lsls", "# = # << #", { 1, 2, 3 } },
		{ 0, "lsr", "# = # >> #", { 1, 2, 3 } },
		{ 0, "lsl", "# = # << #", { 1, 2, 3 } },
		{ 2, "str", "# = #", { 2, 1 } },
		{ 2, "strb", "# = (byte) #", { 2, 1 } },
		{ 2, "strh", "# = (half) #", { 2, 1 } },
		{ 2, "strh.w", "# = (half) #", { 2, 1 } },
		{ 3, "str", "# + # = #", { 2, 3, 1 } },
		{ 3, "strb", "# + # = (byte) #", { 2, 3, 1 } },
		{ 3, "strh", "# + # = (half) #", { 2, 3, 1 } },
		{ 3, "strh.w", "# + # = (half) #", { 2, 3, 1 } },
		{ 3, "sub", "# = # - #", { 1, 2, 3 } },
		{ 3, "subs", "# = # - #", { 1, 2, 3 } },
		{ 3, "fsub", "# = # - #", { 1, 2, 3 } },
		{ 2, "sub", "# -= #", { 1, 2 } }, // THUMB
		{ 2, "subs", "# -= #", { 1, 2 } }, // THUMB
		{ 0, "swp", "swap(#, 2)", { 1 } },
		/* arm thumb */
		{ 0, "movs", "# = #", { 1, 2 } },
		{ 0, "movw", "# = #", { 1, 2 } },
		{ 0, "movt", "# |= # << 16", { 1, 2 } },
		{ 0, "vmov", "# = (float) # . #", { 1, 2, 3 } },
		{ 0, "vdiv.f64", "# = (float) # / #", { 1, 2, 3 } },
		{ 0, "addw", "# = # + #", { 1, 2, 3 } },
		{ 0, "sub.w", "# = # - #", { 1, 2, 3 } },
		{ 0, "tst.w", "if (# == #)", { 1, 2 } },
		{ 0, "lsr.w", "# = # >> #", { 1, 2, 3 } },
		{ 0, "lsl.w", "# = # << #", { 1, 2, 3 } },
		{ 0, "pop.w", "pop #", { 1 } },
		{ 0, "vpop", "pop #", { 1 } },
		{ 0, "vpush", "push #", { 1 } },
		{ 0, "push.w", "push #", { 1 } },
		{ 0, NULL }
	};
	if (!newstr) {
		return false;
	}

	for (i = 0; ops[i].op; i++) {
		if (ops[i].narg) {
			if (argc - 1 != ops[i].narg) {
				continue;
			}
		}
		if (!strcmp (ops[i].op, argv[0])) {
			if (newstr) {
				d = 0;
				j = 0;
				ch = ops[i].str[j];
				for (j = 0, k = 0; ch != '\0'; j++, k++) {
					ch = ops[i].str[j];
					if (ch == '#') {
						if (d >= MAXPSEUDOOPS) {
							// XXX Shouldn't ever happen...
							continue;
						}
						int idx = ops[i].args[d];
						d++;
						if (idx <= 0) {
							// XXX Shouldn't ever happen...
							continue;
						}
						const char *w = argv[idx];
						if (w) {
							strcpy (newstr + k, w);
							k += strlen (w) - 1;
						}
					} else {
						newstr[k] = ch;
					}
				}
				newstr[k] = '\0';
			}

			r_str_replace_char (newstr, '{', '(');
			r_str_replace_char (newstr, '}', ')');
			return true;
		}
	}

	/* TODO: this is slow */
	newstr[0] = '\0';
	for (i = 0; i < argc; i++) {
		strcat (newstr, argv[i]);
		strcat (newstr, (!i || i == argc - 1)? " " : ",");
	}
	r_str_replace_char (newstr, '{', '(');
	r_str_replace_char (newstr, '}', ')');
	return false;
}