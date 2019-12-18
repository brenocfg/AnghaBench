#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* location; int /*<<< orphan*/  relfilenode; } ;
struct TYPE_5__ {struct TYPE_5__* next; TYPE_1__ location; struct TYPE_5__* prev; } ;
typedef  TYPE_2__ ss_lru_item_t ;
struct TYPE_6__ {TYPE_2__* head; TYPE_2__* tail; } ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  void* BlockNumber ;

/* Variables and functions */
 int RelFileNodeEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* scan_locations ; 

__attribute__((used)) static BlockNumber
ss_search(RelFileNode relfilenode, BlockNumber location, bool set)
{
	ss_lru_item_t *item;

	item = scan_locations->head;
	for (;;)
	{
		bool		match;

		match = RelFileNodeEquals(item->location.relfilenode, relfilenode);

		if (match || item->next == NULL)
		{
			/*
			 * If we reached the end of list and no match was found, take over
			 * the last entry
			 */
			if (!match)
			{
				item->location.relfilenode = relfilenode;
				item->location.location = location;
			}
			else if (set)
				item->location.location = location;

			/* Move the entry to the front of the LRU list */
			if (item != scan_locations->head)
			{
				/* unlink */
				if (item == scan_locations->tail)
					scan_locations->tail = item->prev;
				item->prev->next = item->next;
				if (item->next)
					item->next->prev = item->prev;

				/* link */
				item->prev = NULL;
				item->next = scan_locations->head;
				scan_locations->head->prev = item;
				scan_locations->head = item;
			}

			return item->location.location;
		}

		item = item->next;
	}

	/* not reached */
}