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
typedef  int /*<<< orphan*/  u64 ;
struct map {scalar_t__ dso; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* SRCLINE_UNKNOWN ; 
 int fprintf (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 int /*<<< orphan*/  free_srcline (char*) ; 
 char* map__srcline (struct map*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int map__fprintf_srcline(struct map *map, u64 addr, const char *prefix,
			 FILE *fp)
{
	int ret = 0;

	if (map && map->dso) {
		char *srcline = map__srcline(map, addr, NULL);
		if (srcline != SRCLINE_UNKNOWN)
			ret = fprintf(fp, "%s%s", prefix, srcline);
		free_srcline(srcline);
	}
	return ret;
}