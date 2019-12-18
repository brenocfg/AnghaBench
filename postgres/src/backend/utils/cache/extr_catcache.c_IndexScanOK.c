#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int id; } ;
typedef  int /*<<< orphan*/  ScanKey ;
typedef  TYPE_1__ CatCache ;

/* Variables and functions */
#define  AMNAME 133 
#define  AMOID 132 
#define  AUTHMEMMEMROLE 131 
#define  AUTHNAME 130 
#define  AUTHOID 129 
#define  INDEXRELID 128 
 int /*<<< orphan*/  criticalRelcachesBuilt ; 
 int /*<<< orphan*/  criticalSharedRelcachesBuilt ; 

__attribute__((used)) static bool
IndexScanOK(CatCache *cache, ScanKey cur_skey)
{
	switch (cache->id)
	{
		case INDEXRELID:

			/*
			 * Rather than tracking exactly which indexes have to be loaded
			 * before we can use indexscans (which changes from time to time),
			 * just force all pg_index searches to be heap scans until we've
			 * built the critical relcaches.
			 */
			if (!criticalRelcachesBuilt)
				return false;
			break;

		case AMOID:
		case AMNAME:

			/*
			 * Always do heap scans in pg_am, because it's so small there's
			 * not much point in an indexscan anyway.  We *must* do this when
			 * initially building critical relcache entries, but we might as
			 * well just always do it.
			 */
			return false;

		case AUTHNAME:
		case AUTHOID:
		case AUTHMEMMEMROLE:

			/*
			 * Protect authentication lookups occurring before relcache has
			 * collected entries for shared indexes.
			 */
			if (!criticalSharedRelcachesBuilt)
				return false;
			break;

		default:
			break;
	}

	/* Normal case, allow index scan */
	return true;
}