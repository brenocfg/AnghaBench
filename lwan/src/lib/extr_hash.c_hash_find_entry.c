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
struct hash_entry {unsigned int hashval; int /*<<< orphan*/  key; } ;
struct hash_bucket {int used; struct hash_entry* entries; } ;
struct hash {unsigned int n_buckets_mask; scalar_t__ (* key_compare ) (char const*,int /*<<< orphan*/ ) ;struct hash_bucket* buckets; } ;

/* Variables and functions */
 scalar_t__ stub1 (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hash_entry *
hash_find_entry(const struct hash *hash, const char *key, unsigned int hashval)
{
    unsigned int pos = hashval & hash->n_buckets_mask;
    const struct hash_bucket *bucket = hash->buckets + pos;
    struct hash_entry *entry, *entry_end;

    entry = bucket->entries;
    entry_end = entry + bucket->used;
    for (; entry < entry_end; entry++) {
        if (hashval != entry->hashval)
            continue;
        if (hash->key_compare(key, entry->key) == 0)
            return entry;
    }

    return NULL;
}