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
 int /*<<< orphan*/  indexjmp ; 
 int indx (char const**,char const**,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rd_r_rr(const char **p) {
	int i;
	const char *list[] = {
		"iy", "ix", "sp", "hl", "de", "bc", "", "b", "c", "d", "e", "h",
		"l", "( hl )", "a", "( ix +)", "( iy +)", NULL
	};
	i = indx (p, list, 1, &indexjmp);
	if (!i) {
		return 0;
	}
	if (i < 16 && i > 2) {
		return 7 - i;
	}
	if (i > 15) {
		indexed = 0xDD + (i - 16) * 0x20;
		return -7;
	}
	indexed = 0xDD + (2 - i) * 0x20;
	return 3;
}