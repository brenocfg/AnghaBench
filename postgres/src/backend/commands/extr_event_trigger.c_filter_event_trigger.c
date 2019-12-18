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
struct TYPE_3__ {scalar_t__ enabled; scalar_t__ ntags; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ EventTriggerCacheItem ;

/* Variables and functions */
 scalar_t__ SESSION_REPLICATION_ROLE_REPLICA ; 
 scalar_t__ SessionReplicationRole ; 
 scalar_t__ TRIGGER_FIRES_ON_ORIGIN ; 
 scalar_t__ TRIGGER_FIRES_ON_REPLICA ; 
 int /*<<< orphan*/ * bsearch (char const**,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_qsort_strcmp ; 

__attribute__((used)) static bool
filter_event_trigger(const char **tag, EventTriggerCacheItem *item)
{
	/*
	 * Filter by session replication role, knowing that we never see disabled
	 * items down here.
	 */
	if (SessionReplicationRole == SESSION_REPLICATION_ROLE_REPLICA)
	{
		if (item->enabled == TRIGGER_FIRES_ON_ORIGIN)
			return false;
	}
	else
	{
		if (item->enabled == TRIGGER_FIRES_ON_REPLICA)
			return false;
	}

	/* Filter by tags, if any were specified. */
	if (item->ntags != 0 && bsearch(tag, item->tag,
									item->ntags, sizeof(char *),
									pg_qsort_strcmp) == NULL)
		return false;

	/* if we reach that point, we're not filtering out this item */
	return true;
}