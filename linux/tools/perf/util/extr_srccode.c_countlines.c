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
 char* memchr (char*,char,int) ; 

__attribute__((used)) static int countlines(char *map, int maplen)
{
	int numl;
	char *end = map + maplen;
	char *p = map;

	if (maplen == 0)
		return 0;
	numl = 0;
	while (p < end && (p = memchr(p, '\n', end - p)) != NULL) {
		numl++;
		p++;
	}
	if (p < end)
		numl++;
	return numl;
}