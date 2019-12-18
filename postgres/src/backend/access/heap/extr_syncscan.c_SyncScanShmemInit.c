#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* items; TYPE_4__* tail; TYPE_4__* head; } ;
typedef  TYPE_3__ ss_scan_locations_t ;
struct TYPE_6__ {void* relNode; void* dbNode; void* spcNode; } ;
struct TYPE_7__ {int /*<<< orphan*/  location; TYPE_1__ relfilenode; } ;
struct TYPE_9__ {struct TYPE_9__* next; struct TYPE_9__* prev; TYPE_2__ location; } ;
typedef  TYPE_4__ ss_lru_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int SYNC_SCAN_NELEM ; 
 scalar_t__ ShmemInitStruct (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SizeOfScanLocations (int) ; 
 TYPE_3__* scan_locations ; 

void
SyncScanShmemInit(void)
{
	int			i;
	bool		found;

	scan_locations = (ss_scan_locations_t *)
		ShmemInitStruct("Sync Scan Locations List",
						SizeOfScanLocations(SYNC_SCAN_NELEM),
						&found);

	if (!IsUnderPostmaster)
	{
		/* Initialize shared memory area */
		Assert(!found);

		scan_locations->head = &scan_locations->items[0];
		scan_locations->tail = &scan_locations->items[SYNC_SCAN_NELEM - 1];

		for (i = 0; i < SYNC_SCAN_NELEM; i++)
		{
			ss_lru_item_t *item = &scan_locations->items[i];

			/*
			 * Initialize all slots with invalid values. As scans are started,
			 * these invalid entries will fall off the LRU list and get
			 * replaced with real entries.
			 */
			item->location.relfilenode.spcNode = InvalidOid;
			item->location.relfilenode.dbNode = InvalidOid;
			item->location.relfilenode.relNode = InvalidOid;
			item->location.location = InvalidBlockNumber;

			item->prev = (i > 0) ?
				(&scan_locations->items[i - 1]) : NULL;
			item->next = (i < SYNC_SCAN_NELEM - 1) ?
				(&scan_locations->items[i + 1]) : NULL;
		}
	}
	else
		Assert(found);
}