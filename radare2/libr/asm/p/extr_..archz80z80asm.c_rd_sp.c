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
 int indx (char const**,char const**,int /*<<< orphan*/ ,char const**) ; 
 char const* readword ; 

__attribute__((used)) static int rd_sp(const char **p) {
#define SPNN 0
#define SPHL 1
	int i;
	const char *list[] = {
		"hl", "ix", "iy", "(*)", "*", NULL
	};
	const char *nn;
	i = indx (p, list, 0, &nn);
	if (i > 3) {
		readword = nn;
		return i == 4? 2: 0;
	}
	if (i != 1) {
		indexed = 0xDD + 0x20 * (i - 2);
	}
	return 1;
}