#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hash_table_elt {struct hash_table_elt* next; int /*<<< orphan*/  name; } ;
struct hash_table_bucket {int dummy; } ;
struct hash_table {int num_buckets; int /*<<< orphan*/  num_elts; TYPE_1__* buckets; int /*<<< orphan*/  pool; } ;
struct TYPE_4__ {struct hash_table_elt* last; struct hash_table_elt* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 unsigned int hash_table_hash (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pool_alloc (int /*<<< orphan*/ ,int) ; 

void hash_table_add(struct hash_table* ht, struct hash_table_elt* elt)
{
    unsigned                    hash = hash_table_hash(elt->name, ht->num_buckets);

    if (!ht->buckets)
    {
        ht->buckets = pool_alloc(ht->pool, ht->num_buckets * sizeof(struct hash_table_bucket));
        assert(ht->buckets);
        memset(ht->buckets, 0, ht->num_buckets * sizeof(struct hash_table_bucket));
    }

    /* in some cases, we need to get back the symbols of same name in the order
     * in which they've been inserted. So insert new elements at the end of the list.
     */
    if (!ht->buckets[hash].first)
    {
        ht->buckets[hash].first = elt;
    }
    else
    {
        ht->buckets[hash].last->next = elt;
    }
    ht->buckets[hash].last = elt;
    elt->next = NULL;
    ht->num_elts++;
}