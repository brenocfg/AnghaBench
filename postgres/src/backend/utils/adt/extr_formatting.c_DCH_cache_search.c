#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int std; scalar_t__ age; int /*<<< orphan*/  str; scalar_t__ valid; } ;
typedef  TYPE_1__ DCHCacheEntry ;

/* Variables and functions */
 TYPE_1__** DCHCache ; 
 scalar_t__ DCHCounter ; 
 int /*<<< orphan*/  DCH_prevent_counter_overflow () ; 
 int n_DCHCache ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static DCHCacheEntry *
DCH_cache_search(const char *str, bool std)
{
	/* Ensure we can advance DCHCounter below */
	DCH_prevent_counter_overflow();

	for (int i = 0; i < n_DCHCache; i++)
	{
		DCHCacheEntry *ent = DCHCache[i];

		if (ent->valid && strcmp(ent->str, str) == 0 && ent->std == std)
		{
			ent->age = (++DCHCounter);
			return ent;
		}
	}

	return NULL;
}