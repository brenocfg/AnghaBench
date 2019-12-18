#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct map {int /*<<< orphan*/  dso; } ;
struct TYPE_2__ {int /*<<< orphan*/  sym; struct map* map; } ;
struct hist_entry {int /*<<< orphan*/  ip; TYPE_1__ ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  SRCLINE_UNKNOWN ; 
 char* __get_srcline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  map__rip_2objdump (struct map*,int /*<<< orphan*/ ) ; 
 char* no_srcfile ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *hist_entry__get_srcfile(struct hist_entry *e)
{
	char *sf, *p;
	struct map *map = e->ms.map;

	if (!map)
		return no_srcfile;

	sf = __get_srcline(map->dso, map__rip_2objdump(map, e->ip),
			 e->ms.sym, false, true, true, e->ip);
	if (!strcmp(sf, SRCLINE_UNKNOWN))
		return no_srcfile;
	p = strchr(sf, ':');
	if (p && *sf) {
		*p = 0;
		return sf;
	}
	free(sf);
	return no_srcfile;
}