#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  next; } ;
typedef  TYPE_1__ dshash_table_item ;
struct TYPE_8__ {int /*<<< orphan*/  area; } ;
typedef  TYPE_2__ dshash_table ;
typedef  int /*<<< orphan*/  dsa_pointer ;

/* Variables and functions */
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTRY_FROM_ITEM (TYPE_1__*) ; 
 int /*<<< orphan*/  dsa_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ equal_keys (TYPE_2__*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
delete_key_from_bucket(dshash_table *hash_table,
					   const void *key,
					   dsa_pointer *bucket_head)
{
	while (DsaPointerIsValid(*bucket_head))
	{
		dshash_table_item *item;

		item = dsa_get_address(hash_table->area, *bucket_head);

		if (equal_keys(hash_table, key, ENTRY_FROM_ITEM(item)))
		{
			dsa_pointer next;

			next = item->next;
			dsa_free(hash_table->area, *bucket_head);
			*bucket_head = next;

			return true;
		}
		bucket_head = &item->next;
	}
	return false;
}