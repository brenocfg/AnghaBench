#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int replace(int argc, const char *argv[], char *newstr) {
	int i,j,k;
	struct {
		char *op;
		char *str;
	} ops[] = {
		{ "add",     "B += A"},
		{ "addc",    "B += A + t"},
		{ "addv",    "B += A; t = int_overflow (B)"},
		{ "and",     "B &= A"},
		{ "and.b",   "B &= A"},
		{ "bf",      "if (!t) goto A"},
		{ "bf.s",    "if (!t) goto A"},
		{ "bra",     "goto A"},
		{ "brk",     "_break_exception ()"},
		{ "bsr",     "A ()"},
		{ "bsrf",    "A ()"},
		{ "bt",      "if (t) goto A"},
		{ "bt.s",    "if (t) goto A"},
		{ "clrmac",  "_clrmac ()"},
		{ "clrs",    "_clrs ()"},
		{ "clrt",    "_clrt ()"},
		{ "cmp/eq",  "t = B == A ? 1 : 0"},
		{ "cmp/ge",  "t = B >= A ? 1 : 0"},
		{ "cmp/gt",  "t = B > A ? 1 : 0"},
		{ "cmp/hi",  "t = (unsigned) B > (unsigned) A ? 1 : 0"},
		{ "cmp/hs",  "t = (unsigned) B >= (unsigned) A ? 1 : 0"},
		{ "cmp/pl",  "t = A > 0 ? 1 : 0"},
		{ "cmp/pz",  "t = A >= 0 ? 1 : 0"},
		{ "cmp/str", "t = A ^ B ? 1 : 0"},
		{ "div1",    "B /= A"},
		{ "dmuls.l", "mac = B * A"},
		{ "dmulu.l", "mac = (unsigned) B * (unsigned) A"},
		{ "dt",      "A--; t = !A ? 1 : 0"},
		{ "exts.b",  "B = (int) A"},
		{ "extu.b",  "B = (unsigned int) A"},
		{ "exts.w",  "B = (int) A"},
		{ "extu.w",  "B = (unsigned int) A"},
		{ "fabs",    "A = abs (A)"},
		{ "fadd",    "B += A"},
		{ "fcmp/eq", "t = B == A ? 1 : 0"},
		{ "fcmp/gt", "t = B > A ? 1 : 0"},
		{ "fcnvds",  "B = A"},
		{ "fdiv",    "B /= A"},
		{ "flds",    "B = A"},
		{ "fldi0",   "A = 0.0f"},
		{ "fldi1",   "A = 1.0f"},
		{ "float",   "B = A"},
		{ "fmac",    "C += A * B"},
		{ "fmov",    "B = A"},
		{ "fmov.s",  "B = A"},
		{ "fmul",    "B *= A"},
		{ "fneg",    "A = -A"},
		{ "fsqrt",   "A = sqrt (A)"},
		{ "fsts",    "B = A"},
		{ "fsub",    "B -= A"},
		{ "ftrc",    "B = trunc (A)"},
		{ "ftrv",    "B *= A"},
		{ "jmp",     "goto A"},
		{ "jsr",     "A ()"},
		{ "ldr",     "B = A"},
		{ "ldr.l",   "B = A"},
		{ "lds",     "B = A"},
		{ "lds.l",   "B = A"},
		{ "mov",     "B = A"},
		{ "mov.b",   "B = A"},
		{ "mov.l",   "B = A"},
		{ "mov.w",   "B = A"},
		{ "movca.l", "B = A"},
		{ "movt",    "A = t"},
		{ "muls.w",  "macl = A * B"},
		{ "mulu.w",  "macl = (unsigned) A * (unsigned) B"},
		{ "neg",     "A = -A"},
		{ "negc",    "A = (-A) - t"},
		{ "nop",     ""},
		{ "not",     "A = !A"},
		{ "or",      "B |= A"},
		{ "rotcl",   "t = A & 0x80000000 ? 0 : 1; A = (A << 1) | t"},
		{ "rotl",    "A = (A << 1) | (A >> 31)"},
		{ "rotr",    "A = (A << 31) | (A >> 1)"},
		{ "rte",     "_rte ()"},
		{ "rts",     "return"},
		{ "sets",    "s = 1"},
		{ "sett",    "t = 1"},
		{ "shad",    "B = A >= 0 ? B << A : B >> (31 - A)"},
		{ "shal",    "A <<= 1"},
		{ "shar",    "A >>= 1"},
		{ "shld",    "B = A >= 0 ? B << A : B >> (31 - A)"},
		{ "shll",    "A <<= 1"},
		{ "shll2",   "A <<= 2"},
		{ "shll8",   "A <<= 8"},
		{ "shll16",  "A <<= 16"},
		{ "shlr",    "A >>= 1"},
		{ "shlr2",   "A >>= 2"},
		{ "shlr8",   "A >>= 8"},
		{ "shlr16",  "A >>= 16"},
		{ "sleep",   "_halt ()"},
		{ "stc",     "B = A"},
		{ "stc.l",   "B = A"},
		{ "sts",     "B = A"},
		{ "sts.l",   "B = A"},
		{ "sub",     "B -= A"},
		{ "subc",    "B -= A - t"},
		{ "subv",    "B -= A; t = int_underflow (B)"},
		{ "swap.b",  "swap_byte (B, A)"},
		{ "swap.w",  "swap_word (B, A)"},
		{ "tas.b",   "test_and_set (A)"},
		{ "trapa",   "trap (A)"},
		{ "tst",     "t = B & A ? 0 : 1"},
		{ "xor",     "B ^= A"},
		{ "xor.b",   "B ^= A"},
		{ NULL }
	};

	for (i = 0; ops[i].op != NULL; i++) {
		if (!strcmp (ops[i].op, argv[0])) {
			if (newstr != NULL) {
				for (j = k = 0; ops[i].str[j] != '\0'; j++, k++) {
					if (ops[i].str[j] >= 'A' && ops[i].str[j] <= 'J') {
						const char *w = argv[ops[i].str[j] - '@'];
						if (w != NULL) {
							strcpy (newstr + k, w);
							k += strlen(w) - 1;
						}
					} else {
						newstr[k] = ops[i].str[j];
					}
				}
				newstr[k] = '\0';
			}
			return true;
		}
	}

	/* TODO: this is slow */
	if (newstr != NULL) {
		newstr[0] = '\0';
		for (i = 0; i < argc; i++) {
			strcat (newstr, argv[i]);
			strcat (newstr, (i == 0 || i == argc - 1) ? " ":", ");
		}
	}

	return false;
}