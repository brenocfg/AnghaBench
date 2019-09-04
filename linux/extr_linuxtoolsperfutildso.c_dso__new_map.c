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
struct map {int dummy; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 struct dso* dso__new (char const*) ; 
 struct map* map__new2 (int /*<<< orphan*/ ,struct dso*) ; 

struct map *dso__new_map(const char *name)
{
	struct map *map = NULL;
	struct dso *dso = dso__new(name);

	if (dso)
		map = map__new2(0, dso);

	return map;
}