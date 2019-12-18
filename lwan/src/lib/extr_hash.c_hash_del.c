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
struct hash_entry {scalar_t__ key; scalar_t__ value; } ;
struct hash_bucket {int used; int total; struct hash_entry* entries; } ;
struct hash {unsigned int (* hash_value ) (void const*) ;unsigned int n_buckets_mask; int count; int /*<<< orphan*/  (* free_key ) (void*) ;int /*<<< orphan*/  (* free_value ) (void*) ;struct hash_bucket* buckets; } ;

/* Variables and functions */
 int ENOENT ; 
 int MIN_BUCKETS ; 
 int STEPS ; 
 struct hash_entry* hash_find_entry (struct hash*,void const*,unsigned int) ; 
 int hash_n_buckets (struct hash*) ; 
 int /*<<< orphan*/  memcpy (struct hash_entry*,struct hash_entry*,int) ; 
 struct hash_entry* reallocarray (struct hash_entry*,unsigned int,int) ; 
 int /*<<< orphan*/  rehash (struct hash*,int) ; 
 unsigned int stub1 (void const*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (void*) ; 

int hash_del(struct hash *hash, const void *key)
{
    unsigned int hashval = hash->hash_value(key);
    unsigned int pos = hashval & hash->n_buckets_mask;
    struct hash_bucket *bucket = hash->buckets + pos;
    struct hash_entry *entry;

    entry = hash_find_entry(hash, key, hashval);
    if (entry == NULL)
        return -ENOENT;

    hash->free_value((void *)entry->value);
    hash->free_key((void *)entry->key);

    if (bucket->used > 1) {
        /* Instead of compacting the bucket array by moving elements, just copy
         * over the last element on top of the element being removed.  This
         * changes the ordering inside the bucket array, but it's much more
         * efficient, as it always has to copy exactly at most 1 element instead
         * of potentially bucket->used elements. */
        struct hash_entry *entry_last = bucket->entries + bucket->used - 1;

        if (entry != entry_last)
            memcpy(entry, entry_last, sizeof(*entry));
    }

    bucket->used--;
    hash->count--;

    if (hash->n_buckets_mask > (MIN_BUCKETS - 1) && hash->count < hash->n_buckets_mask / 2) {
        rehash(hash, hash_n_buckets(hash) / 2);
    } else {
        unsigned int steps_used = bucket->used / STEPS;
        unsigned int steps_total = bucket->total / STEPS;

        if (steps_used + 1 < steps_total) {
            struct hash_entry *tmp = reallocarray(
                bucket->entries, steps_used + 1, STEPS * sizeof(*tmp));
            if (tmp) {
                bucket->entries = tmp;
                bucket->total = (steps_used + 1) * STEPS;
            }
        }
    }

    return 0;
}