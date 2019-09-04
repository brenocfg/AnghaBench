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
typedef  int /*<<< orphan*/  REgg ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* r_egg_mkvar (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_egg_printf (int /*<<< orphan*/ *,char*,char*,char*,char const*) ; 

__attribute__((used)) static void emit_branch(REgg *egg, char *b, char *g, char *e, char *n, int sz, const char *dst) {
	// This function signature is crap
	char *p, str[64];
	char *arg = NULL;
	char *op = "beq";
	/* NOTE that jb/ja are inverted to fit cmp opcode */
	if (b) {
		*b = '\0';
		op = e?"bge":"bgt";
		arg = b+1;
	} else
	if (g) {
		*g = '\0';
		op = e?"ble":"blt";
		arg = g+1;
	}
	if (!arg) {
		if (e) {
			arg = e+1;
			op = "bne";
		} else {
			arg = "0";
			op = n?"bne":"beq";
		}
	}

	if (*arg == '=') {
		arg++; /* for <=, >=, ... */
	}
	p = r_egg_mkvar (egg, str, arg, 0);
	r_egg_printf (egg, "%s (%s) => (%s)\n", op, p, dst);
	free (p);
}