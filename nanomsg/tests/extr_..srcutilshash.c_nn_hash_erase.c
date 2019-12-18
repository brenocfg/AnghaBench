#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint32_t ;
struct nn_hash_item {int /*<<< orphan*/  list; int /*<<< orphan*/  key; } ;
struct nn_hash {size_t slots; int /*<<< orphan*/  items; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 size_t nn_hash_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_list_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nn_hash_erase (struct nn_hash *self, struct nn_hash_item *item)
{
    uint32_t slot;

    slot = nn_hash_key (item->key) % self->slots;
    nn_list_erase (&self->array [slot], &item->list);
	--self->items;
}