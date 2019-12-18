#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pgssHashKey ;
struct TYPE_7__ {int /*<<< orphan*/  usage; } ;
struct TYPE_5__ {int query_len; int encoding; int /*<<< orphan*/  query_offset; int /*<<< orphan*/  mutex; TYPE_3__ counters; } ;
typedef  TYPE_1__ pgssEntry ;
struct TYPE_6__ {int /*<<< orphan*/  cur_median_usage; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Counters ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USAGE_INIT ; 
 int /*<<< orphan*/  entry_dealloc () ; 
 scalar_t__ hash_get_num_entries (int /*<<< orphan*/ ) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* pgss ; 
 int /*<<< orphan*/  pgss_hash ; 
 scalar_t__ pgss_max ; 

__attribute__((used)) static pgssEntry *
entry_alloc(pgssHashKey *key, Size query_offset, int query_len, int encoding,
			bool sticky)
{
	pgssEntry  *entry;
	bool		found;

	/* Make space if needed */
	while (hash_get_num_entries(pgss_hash) >= pgss_max)
		entry_dealloc();

	/* Find or create an entry with desired hash code */
	entry = (pgssEntry *) hash_search(pgss_hash, key, HASH_ENTER, &found);

	if (!found)
	{
		/* New entry, initialize it */

		/* reset the statistics */
		memset(&entry->counters, 0, sizeof(Counters));
		/* set the appropriate initial usage count */
		entry->counters.usage = sticky ? pgss->cur_median_usage : USAGE_INIT;
		/* re-initialize the mutex each time ... we assume no one using it */
		SpinLockInit(&entry->mutex);
		/* ... and don't forget the query text metadata */
		Assert(query_len >= 0);
		entry->query_offset = query_offset;
		entry->query_len = query_len;
		entry->encoding = encoding;
	}

	return entry;
}