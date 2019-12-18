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
 int addHL ; 
 int indexed ; 
 char const* indexjmp ; 
 int indx (char const**,char const**,int /*<<< orphan*/ ,char const**) ; 
 char const* readbyte ; 
 int writebyte ; 

__attribute__((used)) static int rd_r_add(const char **p) {
#define addHL   15
	int i;
	const char *list[] = {
		"ixl", "ixh", "iyl", "iyh", "b", "c", "d", "e", "h", "l",
		"( hl )", "a", "( ix +)", "( iy +)", "hl", "ix", "iy", "*", NULL
	};
	const char *nn;
	i = indx (p, list, 0, &nn);
	if (i == 18) {	/* expression */
		readbyte = nn;
		writebyte = 1;
		return 7;
	}
	if (i > 14) {	/* hl, ix, iy */
		if (i > 15) {
			indexed = 0xDD + 0x20 * (i - 16);
		}
		return addHL;
	}
	if (i <= 4) {	/* i[xy][hl]  */
		indexed = 0xdd + 0x20 * (i > 2);
		return 6 - (i & 1);
	}
	i -= 4;
	if (i < 9) {
		return i;
	}
	indexed = 0xDD + 0x20 * (i - 9);	/* (i[xy] +) */
	indexjmp = nn;
	return 7;
}