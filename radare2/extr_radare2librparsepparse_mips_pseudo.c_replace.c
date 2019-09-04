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
 scalar_t__ can_replace (char*,int,int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int replace(int argc, const char *argv[], char *newstr) {
	int i,j,k;
	struct {
		char *op;
		char *str;
		int max_operands;
	} ops[] = {
		{ "add", "1 = 2 + 3", 3},
		{ "addi",  "1 = 2 + 3", 3},
		{ "addiu",  "1 = 2 + 3", 3},
		{ "addu",  "1 = 2 + 3", 3},
		{ "and",  "1 = 2 & 3", 3},
		{ "andi",  "1 = 2 & 3", 3},
		{ "b",  "goto 1", 1},
		{ "bal",  "call 1", 1},
		{ "begzal", "if (1 >= 0) call 2", 2},
		{ "beq",  "if (1 == 2) goto 3", 3},
		{ "beqz",  "if (!1) goto 2", 2},
		{ "bgez", "if (1 >= 0) goto 2", 2},
		{ "bgtz", "if (1 > 0) goto 2", 2},
		{ "blez", "if (1 <= 0) goto 2", 2},
		{ "bltz", "if (1 < 0) goto 2", 2},
		{ "bltzal", "if (1 < 0) call 2", 2},
		{ "bne",  "if (1 != 2) goto 3", 3},
		{ "bnez",  "if (1) goto 2", 2},
		{ "j",   "goto 1", 1},
		{ "jal",   "call 1", 1},
		{ "jalr",  "call 1", 1},
		{ "jr",   "goto 1", 1},
		{ "lb",  "1 = byte [3 + 2]", 3},
		{ "lbu",  "1 = (unsigned) byte [3 + 2]", 3},
		{ "lh",  "1 = halfword [3 + 2]", 3},
		{ "lhu",  "1 = (unsigned) halfword [3 + 2]", 3},
		{ "li",   "1 = 2", 2},
		{ "lui",  "1 = 2 << 16", 2},
		{ "lw",  "1 = [3 + 2]", 3},
		{ "mfhi",  "1 = hi", 1},
		{ "mflo",  "1 = lo", 1},
		{ "move",  "1 = 2", 2},
		{ "movn",  "if (3) 1 = 2", 3},
		{ "movz",  "if (!3) 1 = 2", 3},
		{ "mult",  "(hi,lo) = 1 * 2", 2},
		{ "multu",  "unsigned (hi,lo) = 1 * 2", 2},
		{ "mul",  "1 = 2 * 3", 3},
		{ "mulu",  "1 = 2 * 3", 3},
		{ "negu",  "1 = ~2", 2},
		{ "nop",   "", 0},
		{ "nor",   "1 = ~(2 | 3)", 3},
		{ "or",   "1 = 2 | 3", 3},
		{ "ori",   "1 = 2 | 3", 3},
		{ "sb",  "byte [3 + 2] = 1", 3},
		{ "sh",  "halfword [3 + 2] = 1", 3},
		{ "sll",  "1 = 2 << 3", 3},
		{ "sllv",  "1 = 2 << 3", 3},
		{ "slr",  "1 = 2 >> 3", 3}, // logic
		{ "slt",  "1 = (2 < 3)", 3},
		{ "slti",  "1 = (2 < 3)", 3},
		{ "sltiu",  "1 = (unsigned) (2 < 3)", 3},
		{ "sltu",  "1 = (unsigned) (2 < 3)", 3},
		{ "sra",  "1 = (signed) 2 >> 3", 3}, // arithmetic
		{ "srl",  "1 = 2 >> 3", 3},
		{ "srlv",  "1 = 2 >> 3", 3},
		{ "subu",  "1 = 2 - 3", 3},
		{ "sub",  "1 = 2 - 3", 3},
		{ "sw",  "[3 + 2] = 1", 3},
		{ "syscall",  "syscall", 0},
		{ "xor",  "1 = 2 ^ 3", 3},
		{ "xori",  "1 = 2 ^ 3", 3},
		{ NULL }
	};

	for (i=0; ops[i].op != NULL; i++) {
		if (!strcmp (ops[i].op, argv[0])) {
			if (newstr != NULL) {
				for (j=k=0;ops[i].str[j]!='\0';j++,k++) {
					if (can_replace (ops[i].str, j, ops[i].max_operands)) {
						const char *w = argv[ ops[i].str[j]-'0' ];
						if (w != NULL) {
							strcpy (newstr+k, w);
							k += strlen (w) - 1;
						}
					} else {
						newstr[k] = ops[i].str[j];
					}
				}
				newstr[k]='\0';
			}
			return true;
		}
	}

	/* TODO: this is slow */
	if (newstr != NULL) {
		newstr[0] = '\0';
		for (i=0; i<argc; i++) {
			strcat (newstr, argv[i]);
			strcat (newstr, (i == 0 || i== argc - 1)?" ":", ");
		}
	}

	return false;
}