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
 int /*<<< orphan*/  eprintf (char*) ; 
 int indexed ; 
 char const* indexjmp ; 
 int indx (char const**,char const**,int /*<<< orphan*/ ,char const**) ; 
 char const* readbyte ; 
 int writebyte ; 

__attribute__((used)) static int rd_ldbcdehla(const char **p) {
	int i;
	const char *list[] = {
		"b", "c", "d", "e", "h", "l", "( hl )", "a", "( ix +)", "( iy +)", "ixh",
		"ixl", "iyh", "iyl", "*", NULL
	};
	const char *nn;
	i = indx (p, list, 0, &nn);
	if (i == 15) {
		readbyte = nn;
		writebyte = 1;
		return 7;
	}
	if (i > 10) {
		int x;
		x = 0xdd + 0x20 * (i > 12);
		if (indexed && indexed != x) {
			eprintf ("illegal use of index registers\n");
			return 0;
		}
		indexed = x;
		return 6 - (i & 1);
	}
	if (i > 8) {
		if (indexed) {
			eprintf ("illegal use of index registers\n");
			return 0;
		}
		indexed = 0xDD + 0x20 * (i == 10);
		indexjmp = nn;
		return 7;
	}
	return i;
}