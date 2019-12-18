#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dshash_table_item ;
struct TYPE_5__ {int /*<<< orphan*/  key_size; scalar_t__ entry_size; } ;
struct TYPE_6__ {TYPE_1__ params; int /*<<< orphan*/  area; } ;
typedef  TYPE_2__ dshash_table ;
typedef  int /*<<< orphan*/  dsa_pointer ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_FROM_ITEM (int /*<<< orphan*/ *) ; 
 scalar_t__ MAXALIGN (int) ; 
 int /*<<< orphan*/  dsa_allocate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_item_into_bucket (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dshash_table_item *
insert_into_bucket(dshash_table *hash_table,
				   const void *key,
				   dsa_pointer *bucket)
{
	dsa_pointer item_pointer;
	dshash_table_item *item;

	item_pointer = dsa_allocate(hash_table->area,
								hash_table->params.entry_size +
								MAXALIGN(sizeof(dshash_table_item)));
	item = dsa_get_address(hash_table->area, item_pointer);
	memcpy(ENTRY_FROM_ITEM(item), key, hash_table->params.key_size);
	insert_item_into_bucket(hash_table, item_pointer, item, bucket);
	return item;
}