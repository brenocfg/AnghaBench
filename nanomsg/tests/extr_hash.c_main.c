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
typedef  int uint32_t ;
struct nn_hash_item {int dummy; } ;
struct nn_hash {int dummy; } ;

/* Variables and functions */
 struct nn_hash_item* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_free (struct nn_hash_item*) ; 
 int /*<<< orphan*/  nn_hash_erase (struct nn_hash*,struct nn_hash_item*) ; 
 struct nn_hash_item* nn_hash_get (struct nn_hash*,int) ; 
 int /*<<< orphan*/  nn_hash_init (struct nn_hash*) ; 
 int /*<<< orphan*/  nn_hash_insert (struct nn_hash*,int,struct nn_hash_item*) ; 
 int /*<<< orphan*/  nn_hash_item_init (struct nn_hash_item*) ; 
 int /*<<< orphan*/  nn_hash_term (struct nn_hash*) ; 

int main ()
{
    struct nn_hash hash;
    uint32_t k;
    struct nn_hash_item *item;
    struct nn_hash_item *item5000 = NULL;

    nn_hash_init (&hash);

    /*  Insert 10000 elements into the hash table. */
    for (k = 0; k != 10000; ++k) {
        item = nn_alloc (sizeof (struct nn_hash_item), "item");
        nn_assert (item);
        if (k == 5000)
            item5000 = item;
        nn_hash_item_init (item);
        nn_hash_insert (&hash, k, item);
    }

    /*  Find one element and check whether it is the correct one. */
    nn_assert (nn_hash_get (&hash, 5000) == item5000);

    /*  Remove all the elements from the hash table and terminate it. */
    for (k = 0; k != 10000; ++k) {
        item = nn_hash_get (&hash, k);
        nn_hash_erase (&hash, item);
        nn_free (item);
    }
    nn_hash_term (&hash);

    return 0;
}