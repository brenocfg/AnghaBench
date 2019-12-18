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
 int /*<<< orphan*/  eprintf (char*,...) ; 
 scalar_t__ r_num_get (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__* regs ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int getreg(const char *p) {
	int n;
	if (!p || !*p) {
		eprintf ("Missing argument\n");
		return -1;
	}
	/* check if it's a register */
	for (n = 0; regs[n]; n++) {
		if (!strcmp (p, regs[n])) {
			return n;
		}
	}
	/* try to convert it into a number */
	if (p[0] == '-') {
		n = (int) r_num_get (NULL, &p[1]);
		n = -n;
	} else {
		n = (int) r_num_get (NULL, p);
	}
	if (n != 0 || p[0] == '0') {
		return n;
	}
	eprintf ("Invalid reg name (%s) at pos %d\n", p, n);
	return -1;
}