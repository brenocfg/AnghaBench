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
 char* fdt_getprop (void const*,unsigned long,char*,int*) ; 
 scalar_t__ of_compat_cmp (char const*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int of_fdt_is_compatible(const void *blob,
		      unsigned long node, const char *compat)
{
	const char *cp;
	int cplen;
	unsigned long l, score = 0;

	cp = fdt_getprop(blob, node, "compatible", &cplen);
	if (cp == NULL)
		return 0;
	while (cplen > 0) {
		score++;
		if (of_compat_cmp(cp, compat, strlen(compat)) == 0)
			return score;
		l = strlen(cp) + 1;
		cp += l;
		cplen -= l;
	}

	return 0;
}