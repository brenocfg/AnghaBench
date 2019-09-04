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
 int indx (char const**,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rd_jp(const char **p) {
	int i;
	const char *list[] = {
		"nz", "z", "nc", "c", "po", "pe", "p", "m", "( ix )", "( iy )",
		"(hl)", NULL
	};
	i = indx (p, list, 0, NULL);
	if (i < 9) {
		return i;
	}
	if (i == 11) {
		return -1;
	}
	indexed = 0xDD + 0x20 * (i - 9);
	return -1;
}