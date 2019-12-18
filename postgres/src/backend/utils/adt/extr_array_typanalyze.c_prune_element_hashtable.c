#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int frequency; int delta; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ TrackItem ;
struct TYPE_4__ {int /*<<< orphan*/  typbyval; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 TYPE_2__* array_extra_data ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * hash_search (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prune_element_hashtable(HTAB *elements_tab, int b_current)
{
	HASH_SEQ_STATUS scan_status;
	TrackItem  *item;

	hash_seq_init(&scan_status, elements_tab);
	while ((item = (TrackItem *) hash_seq_search(&scan_status)) != NULL)
	{
		if (item->frequency + item->delta <= b_current)
		{
			Datum		value = item->key;

			if (hash_search(elements_tab, (const void *) &item->key,
							HASH_REMOVE, NULL) == NULL)
				elog(ERROR, "hash table corrupted");
			/* We should free memory if element is not passed by value */
			if (!array_extra_data->typbyval)
				pfree(DatumGetPointer(value));
		}
	}
}