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
struct TYPE_4__ {scalar_t__ age; int /*<<< orphan*/  str; scalar_t__ valid; } ;
typedef  TYPE_1__ NUMCacheEntry ;

/* Variables and functions */
 TYPE_1__** NUMCache ; 
 scalar_t__ NUMCounter ; 
 int /*<<< orphan*/  NUM_prevent_counter_overflow () ; 
 int n_NUMCache ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static NUMCacheEntry *
NUM_cache_search(const char *str)
{
	/* Ensure we can advance NUMCounter below */
	NUM_prevent_counter_overflow();

	for (int i = 0; i < n_NUMCache; i++)
	{
		NUMCacheEntry *ent = NUMCache[i];

		if (ent->valid && strcmp(ent->str, str) == 0)
		{
			ent->age = (++NUMCounter);
			return ent;
		}
	}

	return NULL;
}