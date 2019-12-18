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
struct hash_entry {int used; struct hash_entry* entries; int /*<<< orphan*/  value; int /*<<< orphan*/  key; int /*<<< orphan*/  hashval; } ;
struct hash_bucket {int used; struct hash_bucket* entries; int /*<<< orphan*/  value; int /*<<< orphan*/  key; int /*<<< orphan*/  hashval; } ;
struct hash {scalar_t__ count; unsigned int n_buckets_mask; struct hash_entry* buckets; } ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct hash_entry* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  free (struct hash_entry*) ; 
 struct hash_entry* hash_add_entry_hashed (struct hash*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int hash_n_buckets (struct hash*) ; 

__attribute__((used)) static void rehash(struct hash *hash, unsigned int new_bucket_size)
{
    struct hash_bucket *buckets = calloc(new_bucket_size, sizeof(*buckets));
    const struct hash_bucket *bucket_end = hash->buckets + hash_n_buckets(hash);
    const struct hash_bucket *bucket;
    struct hash hash_copy = *hash;

    assert((new_bucket_size & (new_bucket_size - 1)) == 0);
    assert(hash_n_buckets(hash) != new_bucket_size);

    if (buckets == NULL)
        return;

    hash_copy.count = 0;
    hash_copy.n_buckets_mask = new_bucket_size - 1;
    hash_copy.buckets = buckets;

    for (bucket = hash->buckets; bucket < bucket_end; bucket++) {
        const struct hash_entry *old = bucket->entries;
        const struct hash_entry *old_end = old + bucket->used;

        for (; old < old_end; old++) {
            struct hash_entry *new;

            new = hash_add_entry_hashed(&hash_copy, old->key, old->hashval);
            if (UNLIKELY(!new))
                goto fail;

            new->key = old->key;
            new->value = old->value;
        }
    }

    /* Original table must remain untouched in the event resizing fails:
     * previous loop may return early on allocation failure, so can't free
     * bucket entry arrays there.  */
    for (bucket = hash->buckets; bucket < bucket_end; bucket++)
        free(bucket->entries);
    free(hash->buckets);

    hash->buckets = buckets;
    hash->n_buckets_mask = new_bucket_size - 1;

    assert(hash_copy.count == hash->count);

    return;

fail:
    for (bucket_end = bucket, bucket = hash->buckets; bucket < bucket_end;
         bucket++)
        free(bucket->entries);

    free(buckets);
}