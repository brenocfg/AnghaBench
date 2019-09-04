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
 int indx (char const**,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readbyte ; 
 int writebyte ; 

__attribute__((used)) static int rd_ld_hl(const char **p) {
	int i;
	const char *list[] = {
		"b", "c", "d", "e", "h", "l", "", "a", "*", NULL
	};
	i = indx (p, list, 0, &readbyte);
	if (i < 9) {
		return i;
	}
	writebyte = 1;
	return 7;
}