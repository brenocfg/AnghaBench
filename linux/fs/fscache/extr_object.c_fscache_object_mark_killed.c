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
struct fscache_object {TYPE_1__* cache; int /*<<< orphan*/  flags; } ;
typedef  enum fscache_why_object_killed { ____Placeholder_fscache_why_object_killed } fscache_why_object_killed ;
struct TYPE_2__ {int /*<<< orphan*/  identifier; } ;

/* Variables and functions */
#define  FSCACHE_OBJECT_IS_STALE 131 
 int /*<<< orphan*/  FSCACHE_OBJECT_KILLED_BY_CACHE ; 
#define  FSCACHE_OBJECT_NO_SPACE 130 
#define  FSCACHE_OBJECT_WAS_CULLED 129 
#define  FSCACHE_OBJECT_WAS_RETIRED 128 
 int /*<<< orphan*/  fscache_n_cache_culled_objects ; 
 int /*<<< orphan*/  fscache_n_cache_no_space_reject ; 
 int /*<<< orphan*/  fscache_n_cache_retired_objects ; 
 int /*<<< orphan*/  fscache_n_cache_stale_objects ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fscache_object_mark_killed(struct fscache_object *object,
				enum fscache_why_object_killed why)
{
	if (test_and_set_bit(FSCACHE_OBJECT_KILLED_BY_CACHE, &object->flags)) {
		pr_err("Error: Object already killed by cache [%s]\n",
		       object->cache->identifier);
		return;
	}

	switch (why) {
	case FSCACHE_OBJECT_NO_SPACE:
		fscache_stat(&fscache_n_cache_no_space_reject);
		break;
	case FSCACHE_OBJECT_IS_STALE:
		fscache_stat(&fscache_n_cache_stale_objects);
		break;
	case FSCACHE_OBJECT_WAS_RETIRED:
		fscache_stat(&fscache_n_cache_retired_objects);
		break;
	case FSCACHE_OBJECT_WAS_CULLED:
		fscache_stat(&fscache_n_cache_culled_objects);
		break;
	}
}