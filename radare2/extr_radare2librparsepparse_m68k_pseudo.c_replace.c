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
		{ "move",  "2 = 1", 2},
		{ "movea",  "2 = 1", 2},
		{ "moveq",  "2 = 1", 2},
		{ "movem",  "2 = 1", 2},
		{ "lea",  "2 = 1", 2},
		{ "bsr",  "1()", 1},
		{ "jsr",  "1()", 1},
		{ "beq",  "if (==) jmp 1", 1},
		{ "blt",  "if (<) jmp 1", 1},
		{ "ble",  "if (<=) jmp 1", 1},
		{ "bgt",  "if (>) jmp 1", 1},
		{ "bge",  "if (>=) jmp 1", 1},
		{ "bcs",  "if (cs) jmp 1", 1},
		{ "bcc",  "if (cc) jmp 1", 1},
		{ "bra",  "jmp 1", 1},
		{ "jmp",  "jmp 1", 1},
		{ "rts",  "ret", 2},
		{ "btst",  "1 == 2", 2},
		{ "cmp",  "1 == 2", 2},
		{ "cmpi",  "2 == 1", 2},
		{ "add",  "1 += 2", 2},
		{ "addi",  "1 += 2", 2},
		{ "adda",  "1 += 2", 2},
		{ "sub",  "1 += 2", 2},
		{ "subq",  "1 += 2", 2},
		{ "tst",  "1 == 2", 2},
		{ "ori",  "2 |= 1", 2},
		{ "or",  "2 |= 1", 2},
		{ "lsr",  "2 >>= 1", 2},
		{ "lsl",  "2 <<= 1", 2},
		{ "andi",  "2 &= 1", 2},
		{ "nop",  ""},
//
		{ NULL }
	};

	for (i=0; ops[i].op != NULL; i++) {
		if (!strcmp (ops[i].op, argv[0])) {
			if (newstr != NULL) {
				for (j=k=0;ops[i].str[j]!='\0';j++,k++) {
					if (can_replace(ops[i].str, j, ops[i].max_operands)) {
						const char *w = argv[ ops[i].str[j]-'0' ];
						if (w != NULL) {
							strcpy (newstr+k, w);
							k += strlen(w)-1;
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