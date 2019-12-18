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
struct hash_entry {void const* value; void const* key; } ;
struct hash {scalar_t__ count; scalar_t__ n_buckets_mask; int /*<<< orphan*/  (* free_key ) (void*) ;int /*<<< orphan*/  (* free_value ) (void*) ;} ;

/* Variables and functions */
 int errno ; 
 struct hash_entry* hash_add_entry (struct hash*,void const*) ; 
 int hash_n_buckets (struct hash*) ; 
 int /*<<< orphan*/  rehash (struct hash*,int) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

int hash_add(struct hash *hash, const void *key, const void *value)
{
    struct hash_entry *entry = hash_add_entry(hash, key);

    if (!entry)
        return -errno;

    hash->free_value((void *)entry->value);
    hash->free_key((void *)entry->key);

    entry->key = key;
    entry->value = value;

    if (hash->count > hash->n_buckets_mask)
        rehash(hash, hash_n_buckets(hash) * 2);

    return 0;
}