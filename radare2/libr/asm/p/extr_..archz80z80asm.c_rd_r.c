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
 int indexed ; 
 char const* indexjmp ; 
 int indx (char const**,char const**,int /*<<< orphan*/ ,char const**) ; 
 char const* readbyte ; 
 int writebyte ; 

__attribute__((used)) static int rd_r(const char **p) {
	int i;
	const char *nn;
	const char *list[] = {
		"ixl", "ixh", "iyl", "iyh", "b", "c", "d", "e", "h", "l", "( hl )",
		"a", "( ix +)", "( iy +)", "*", NULL
	};
	i = indx (p, list, 0, &nn);
	if (i == 15) {	/* expression */
		readbyte = nn;
		writebyte = 1;
		return 7;
	}
	if (i <= 4) {
		indexed = 0xdd + 0x20 * (i > 2);
		return 6 - (i & 1);
	}
	i -= 4;
	if (i < 9) {
		return i;
	}
	indexed = 0xDD + 0x20 * (i - 9);
	indexjmp = nn;
	return 7;
}