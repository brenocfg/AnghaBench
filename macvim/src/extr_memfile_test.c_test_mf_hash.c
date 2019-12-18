#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int mht_count; int mht_mask; scalar_t__ mht_buckets; scalar_t__ mht_small_buckets; } ;
typedef  TYPE_1__ mf_hashtab_T ;
struct TYPE_13__ {scalar_t__ mhi_key; } ;
typedef  TYPE_2__ mf_hashitem_T ;
typedef  int long_u ;
typedef  scalar_t__ blocknr_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MHT_GROWTH_FACTOR ; 
 int MHT_INIT_SIZE ; 
 int MHT_LOG_LOAD_FACTOR ; 
 int TEST_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ index_to_key (int) ; 
 scalar_t__ lalloc_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mf_hash_add_item (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* mf_hash_find (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mf_hash_free_all (TYPE_1__*) ; 
 int /*<<< orphan*/  mf_hash_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mf_hash_rem_item (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vim_free (TYPE_2__*) ; 

__attribute__((used)) static void
test_mf_hash()
{
    mf_hashtab_T   ht;
    mf_hashitem_T  *item;
    blocknr_T      key;
    long_u	   i;
    long_u	   num_buckets;

    mf_hash_init(&ht);

    /* insert some items and check invariants */
    for (i = 0; i < TEST_COUNT; i++)
    {
	assert(ht.mht_count == i);

	/* check that number of buckets is a power of 2 */
	num_buckets = ht.mht_mask + 1;
	assert(num_buckets > 0 && (num_buckets & (num_buckets - 1)) == 0);

	/* check load factor */
	assert(ht.mht_count <= (num_buckets << MHT_LOG_LOAD_FACTOR));

	if (i < (MHT_INIT_SIZE << MHT_LOG_LOAD_FACTOR))
	{
	    /* first expansion shouldn't have occurred yet */
	    assert(num_buckets == MHT_INIT_SIZE);
	    assert(ht.mht_buckets == ht.mht_small_buckets);
	}
	else
	{
	    assert(num_buckets > MHT_INIT_SIZE);
	    assert(ht.mht_buckets != ht.mht_small_buckets);
	}

	key = index_to_key(i);
	assert(mf_hash_find(&ht, key) == NULL);

	/* allocate and add new item */
	item = (mf_hashitem_T *)lalloc_clear(sizeof(mf_hashtab_T), FALSE);
	assert(item != NULL);
	item->mhi_key = key;
	mf_hash_add_item(&ht, item);

	assert(mf_hash_find(&ht, key) == item);

	if (ht.mht_mask + 1 != num_buckets)
	{
	    /* hash table was expanded */
	    assert(ht.mht_mask + 1 == num_buckets * MHT_GROWTH_FACTOR);
	    assert(i + 1 == (num_buckets << MHT_LOG_LOAD_FACTOR));
	}
    }

    /* check presence of inserted items */
    for (i = 0; i < TEST_COUNT; i++)
    {
	key = index_to_key(i);
	item = mf_hash_find(&ht, key);
	assert(item != NULL);
	assert(item->mhi_key == key);
    }

    /* delete some items */
    for (i = 0; i < TEST_COUNT; i++)
    {
	if (i % 100 < 70)
	{
	    key = index_to_key(i);
	    item = mf_hash_find(&ht, key);
	    assert(item != NULL);
	    assert(item->mhi_key == key);

	    mf_hash_rem_item(&ht, item);
	    assert(mf_hash_find(&ht, key) == NULL);

	    mf_hash_add_item(&ht, item);
	    assert(mf_hash_find(&ht, key) == item);

	    mf_hash_rem_item(&ht, item);
	    assert(mf_hash_find(&ht, key) == NULL);

	    vim_free(item);
	}
    }

    /* check again */
    for (i = 0; i < TEST_COUNT; i++)
    {
	key = index_to_key(i);
	item = mf_hash_find(&ht, key);

	if (i % 100 < 70)
	{
	    assert(item == NULL);
	}
	else
	{
	    assert(item != NULL);
	    assert(item->mhi_key == key);
	}
    }

    /* free hash table and all remaining items */
    mf_hash_free_all(&ht);
}