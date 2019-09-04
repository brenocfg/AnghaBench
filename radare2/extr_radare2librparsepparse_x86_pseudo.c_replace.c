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
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int member_4; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int replace (int argc, char *argv[], char *newstr) {
#define MAXPSEUDOOPS 10
	int i, j, k, d;
	char ch;
	struct {
		char *op;
		char *str;
		int args[MAXPSEUDOOPS];  // XXX can't use flex arrays, all unused will be 0
	} ops[] = {
		{ "adc",  "# += #", {1, 2}},
		{ "add",  "# += #", {1, 2}},
		{ "and",  "# &= #", {1, 2}},
		{ "call", "# ()", {1}},
		{ "cmove", "if (!var) # = #", {1, 2}},
		{ "cmovl","if (var < 0) # = #", {1, 2}},
		{ "cmp", "var = # - #", {1, 2}},
		{ "cmpsq", "var = # - #", {1, 2}},
		{ "cmpsb", "while (CX != 0) { var = *(DS*16 + SI) - *(ES*16 + DI); SI++; DI++; CX--; if (!var) break; }", {0}},
		{ "cmpsw", "while (CX != 0) { var = *(DS*16 + SI) - *(ES*16 + DI); SI+=4; DI+=4; CX--; if (!var) break; }", {0}},
		{ "dec",  "#--", {1}},
		{ "div",  "# /= #", {1, 2}},
		{ "fabs",  "abs(#)", {1}},
		{ "fadd",  "# = # + #", {1, 1, 2}},
		{ "fcomp",  "var = # - #", {1, 2}},
		{ "fcos",  "# = cos(#)", {1, 1}},
		{ "fdiv",  "# = # / #", {1, 1, 2}},
		{ "fiadd",  "# = # / #", {1, 1, 2}},
		{ "ficom",  "var = # - #", {1, 2}},
		{ "fidiv",  "# = # / #", {1, 1, 2}},
		{ "fidiv",  "# = # * #", {1, 1, 2}},
		{ "fisub",  "# = # - #", {1, 1, 2}},
		{ "fnul",  "# = # * #", {1, 1, 2}},
		{ "fnop",  " ", {0}},
		{ "frndint",  "# = (int) #", {1, 1}},
		{ "fsin",  "# = sin(#)", {1, 1}},
		{ "fsqrt",  "# = sqrt(#)", {1, 1}},
		{ "fsub",  "# = # - #", {1, 1, 2}},
		{ "fxch",  "#,# = #,#", {1, 2, 2, 1}},
		{ "idiv",  "# /= #", {1, 2}},
		{ "imul",  "# = # * #", {1, 2, 3}},
		{ "in",   "# = io[#]", {1, 2}},
		{ "inc",  "#++", {1}},
		{ "ja", "if (((unsigned) var) > 0) goto #", {1}},
		{ "jb", "if (((unsigned) var) < 0) goto #", {1}},
		{ "jbe", "if (((unsigned) var) <= 0) goto #", {1}},
		{ "je", "if (!var) goto #", {1}},
		{ "jg", "if (var > 0) goto #", {1}},
		{ "jge", "if (var >= 0) goto #", {1}},
		{ "jle", "if (var <= 0) goto #", {1}},
		{ "jmp",  "goto #", {1}},
		{ "jne", "if (var) goto #", {1}},
		{ "lea",  "# = #", {1, 2}},
		{ "mov",  "# = #", {1, 2}},
		{ "movq",  "# = #", {1, 2}},
		{ "movaps",  "# = #", {1, 2}},
		{ "movups",  "# = #", {1, 2}},
		{ "movsd",  "# = #", {1, 2}},
		{ "movsx","# = #", {1, 2}},
		{ "movsxd","# = #", {1, 2}},
		{ "movzx", "# = #", {1, 2}},
		{ "movntdq", "# = #", {1, 2}},
		{ "movnti", "# = #", {1, 2}},
		{ "movntpd", "# = #", {1, 2}},
		{ "pcmpeqb", "# == #", {1, 2}},

		{ "movdqu", "# = #", {1, 2}},
		{ "movdqa", "# = #", {1, 2}},
		{ "pextrb", "# = (byte) # [#]", {1, 2, 3}},
		{ "palignr", "# = # align #", {1, 2, 3}},
		{ "pxor", "# ^= #", {1, 2}},
		{ "xorps", "# ^= #", {1, 2}},
		{ "mul",  "# = # * #", {1, 2, 3}},
		{ "mulss",  "# = # * #", {1, 2, 3}},
		{ "neg",  "# ~= #", {1, 1}},
		{ "nop",  "", {0}},
		{ "not",  "# = !#", {1, 1}},
		{ "or",   "# |= #", {1, 2}},
		{ "out",  "io[#] = #", {1, 2}},
		{ "pop",  "pop #", {1}},
		{ "push", "push #", {1}},
		{ "ret",  "return", {0}},
		{ "sal",  "# <<= #", {1, 2}},
		{ "sar",  "# >>= #", {1, 2}},
		{ "sete",  "# = e", {1}},
		{ "setne",  "# = ne", {1}},
		{ "shl",  "# <<<= #", {1, 2}},
		{ "shld",  "# <<<= #", {1, 2}},
		{ "sbb",  "# = # - #", {1, 1, 2}},
		{ "shr",  "# >>>= #", {1, 2}},
		{ "shlr",  "# >>>= #", {1, 2}},
		//{ "strd",  "# = # - #", {1, 2, 3}},
		{ "sub",  "# -= #", {1, 2}},
		{ "swap", "var = #; # = #; # = var", {1, 1, 2, 2}},
		{ "test", "var = # & #", {1, 2}},
		{ "xchg",  "#,# = #,#", {1, 2, 2, 1}},
		{ "xadd",  "#,# = #,#+#", {1, 2, 2, 1, 2}},
		{ "xor",  "# ^= #", {1, 2}},
		{ NULL }
	};

	if (argc > 2 && !strcmp (argv[0], "xor")) {
		if (!strcmp (argv[1], argv[2])) {
			argv[0] = "mov";
			argv[2] = "0";
		}
	}
	for (i = 0; ops[i].op != NULL; i++) {
		if (!strcmp (ops[i].op, argv[0])) {
			if (newstr != NULL) {
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
						if (w != NULL) {
							strcpy (newstr + k, w);
							k += strlen (w) - 1;
						}
					} else {
						newstr[k] = ch;
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
		for (i=0; i<argc; i++) {
			strcat (newstr, argv[i]);
			strcat (newstr, (i == 0 || i== argc - 1)?" ":",");
		}
	}
	return false;
#undef MAXPSEUDOOPS
}