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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_raid_bio {int nr_pages; int real_stripes; int stripe_npages; int faila; int failb; int nr_data; void* finish_pbitmap; void* dbitmap; void* finish_pointers; void* bio_pages; void* stripe_pages; int /*<<< orphan*/  stripes_pending; int /*<<< orphan*/  error; int /*<<< orphan*/  refs; int /*<<< orphan*/  stripe_len; struct btrfs_fs_info* fs_info; struct btrfs_bio* bbio; int /*<<< orphan*/  hash_list; int /*<<< orphan*/  stripe_cache; int /*<<< orphan*/  bio_list_lock; int /*<<< orphan*/  plug_list; int /*<<< orphan*/  bio_list; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_bio {int num_stripes; int num_tgtdevs; int map_type; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int BTRFS_BLOCK_GROUP_RAID5 ; 
 int BTRFS_BLOCK_GROUP_RAID6 ; 
 int /*<<< orphan*/  BUG () ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct btrfs_raid_bio* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 struct btrfs_raid_bio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int rbio_nr_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct btrfs_raid_bio *alloc_rbio(struct btrfs_fs_info *fs_info,
					 struct btrfs_bio *bbio,
					 u64 stripe_len)
{
	struct btrfs_raid_bio *rbio;
	int nr_data = 0;
	int real_stripes = bbio->num_stripes - bbio->num_tgtdevs;
	int num_pages = rbio_nr_pages(stripe_len, real_stripes);
	int stripe_npages = DIV_ROUND_UP(stripe_len, PAGE_SIZE);
	void *p;

	rbio = kzalloc(sizeof(*rbio) +
		       sizeof(*rbio->stripe_pages) * num_pages +
		       sizeof(*rbio->bio_pages) * num_pages +
		       sizeof(*rbio->finish_pointers) * real_stripes +
		       sizeof(*rbio->dbitmap) * BITS_TO_LONGS(stripe_npages) +
		       sizeof(*rbio->finish_pbitmap) *
				BITS_TO_LONGS(stripe_npages),
		       GFP_NOFS);
	if (!rbio)
		return ERR_PTR(-ENOMEM);

	bio_list_init(&rbio->bio_list);
	INIT_LIST_HEAD(&rbio->plug_list);
	spin_lock_init(&rbio->bio_list_lock);
	INIT_LIST_HEAD(&rbio->stripe_cache);
	INIT_LIST_HEAD(&rbio->hash_list);
	rbio->bbio = bbio;
	rbio->fs_info = fs_info;
	rbio->stripe_len = stripe_len;
	rbio->nr_pages = num_pages;
	rbio->real_stripes = real_stripes;
	rbio->stripe_npages = stripe_npages;
	rbio->faila = -1;
	rbio->failb = -1;
	refcount_set(&rbio->refs, 1);
	atomic_set(&rbio->error, 0);
	atomic_set(&rbio->stripes_pending, 0);

	/*
	 * the stripe_pages, bio_pages, etc arrays point to the extra
	 * memory we allocated past the end of the rbio
	 */
	p = rbio + 1;
#define CONSUME_ALLOC(ptr, count)	do {				\
		ptr = p;						\
		p = (unsigned char *)p + sizeof(*(ptr)) * (count);	\
	} while (0)
	CONSUME_ALLOC(rbio->stripe_pages, num_pages);
	CONSUME_ALLOC(rbio->bio_pages, num_pages);
	CONSUME_ALLOC(rbio->finish_pointers, real_stripes);
	CONSUME_ALLOC(rbio->dbitmap, BITS_TO_LONGS(stripe_npages));
	CONSUME_ALLOC(rbio->finish_pbitmap, BITS_TO_LONGS(stripe_npages));
#undef  CONSUME_ALLOC

	if (bbio->map_type & BTRFS_BLOCK_GROUP_RAID5)
		nr_data = real_stripes - 1;
	else if (bbio->map_type & BTRFS_BLOCK_GROUP_RAID6)
		nr_data = real_stripes - 2;
	else
		BUG();

	rbio->nr_data = nr_data;
	return rbio;
}