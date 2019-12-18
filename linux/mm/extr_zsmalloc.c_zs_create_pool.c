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
struct zs_pool {struct size_class** size_class; int /*<<< orphan*/  migration_wait; int /*<<< orphan*/  name; } ;
struct size_class {int size; int index; int pages_per_zspage; int objs_per_zspage; int /*<<< orphan*/ * fullness_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NR_ZS_FULLNESS ; 
 int PAGE_SIZE ; 
 int ZS_EMPTY ; 
 int ZS_HANDLE_SIZE ; 
 int ZS_MAX_ALLOC_SIZE ; 
 int ZS_MIN_ALLOC_SIZE ; 
 int ZS_SIZE_CLASSES ; 
 int ZS_SIZE_CLASS_DELTA ; 
 scalar_t__ can_merge (struct size_class*,int,int) ; 
 scalar_t__ create_cache (struct zs_pool*) ; 
 int get_pages_per_zspage (int) ; 
 int huge_class_size ; 
 int /*<<< orphan*/  init_deferred_free (struct zs_pool*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zs_destroy_pool (struct zs_pool*) ; 
 int /*<<< orphan*/  zs_pool_stat_create (struct zs_pool*,char const*) ; 
 scalar_t__ zs_register_migration (struct zs_pool*) ; 
 int /*<<< orphan*/  zs_register_shrinker (struct zs_pool*) ; 

struct zs_pool *zs_create_pool(const char *name)
{
	int i;
	struct zs_pool *pool;
	struct size_class *prev_class = NULL;

	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		return NULL;

	init_deferred_free(pool);

	pool->name = kstrdup(name, GFP_KERNEL);
	if (!pool->name)
		goto err;

#ifdef CONFIG_COMPACTION
	init_waitqueue_head(&pool->migration_wait);
#endif

	if (create_cache(pool))
		goto err;

	/*
	 * Iterate reversely, because, size of size_class that we want to use
	 * for merging should be larger or equal to current size.
	 */
	for (i = ZS_SIZE_CLASSES - 1; i >= 0; i--) {
		int size;
		int pages_per_zspage;
		int objs_per_zspage;
		struct size_class *class;
		int fullness = 0;

		size = ZS_MIN_ALLOC_SIZE + i * ZS_SIZE_CLASS_DELTA;
		if (size > ZS_MAX_ALLOC_SIZE)
			size = ZS_MAX_ALLOC_SIZE;
		pages_per_zspage = get_pages_per_zspage(size);
		objs_per_zspage = pages_per_zspage * PAGE_SIZE / size;

		/*
		 * We iterate from biggest down to smallest classes,
		 * so huge_class_size holds the size of the first huge
		 * class. Any object bigger than or equal to that will
		 * endup in the huge class.
		 */
		if (pages_per_zspage != 1 && objs_per_zspage != 1 &&
				!huge_class_size) {
			huge_class_size = size;
			/*
			 * The object uses ZS_HANDLE_SIZE bytes to store the
			 * handle. We need to subtract it, because zs_malloc()
			 * unconditionally adds handle size before it performs
			 * size class search - so object may be smaller than
			 * huge class size, yet it still can end up in the huge
			 * class because it grows by ZS_HANDLE_SIZE extra bytes
			 * right before class lookup.
			 */
			huge_class_size -= (ZS_HANDLE_SIZE - 1);
		}

		/*
		 * size_class is used for normal zsmalloc operation such
		 * as alloc/free for that size. Although it is natural that we
		 * have one size_class for each size, there is a chance that we
		 * can get more memory utilization if we use one size_class for
		 * many different sizes whose size_class have same
		 * characteristics. So, we makes size_class point to
		 * previous size_class if possible.
		 */
		if (prev_class) {
			if (can_merge(prev_class, pages_per_zspage, objs_per_zspage)) {
				pool->size_class[i] = prev_class;
				continue;
			}
		}

		class = kzalloc(sizeof(struct size_class), GFP_KERNEL);
		if (!class)
			goto err;

		class->size = size;
		class->index = i;
		class->pages_per_zspage = pages_per_zspage;
		class->objs_per_zspage = objs_per_zspage;
		spin_lock_init(&class->lock);
		pool->size_class[i] = class;
		for (fullness = ZS_EMPTY; fullness < NR_ZS_FULLNESS;
							fullness++)
			INIT_LIST_HEAD(&class->fullness_list[fullness]);

		prev_class = class;
	}

	/* debug only, don't abort if it fails */
	zs_pool_stat_create(pool, name);

	if (zs_register_migration(pool))
		goto err;

	/*
	 * Not critical since shrinker is only used to trigger internal
	 * defragmentation of the pool which is pretty optional thing.  If
	 * registration fails we still can use the pool normally and user can
	 * trigger compaction manually. Thus, ignore return code.
	 */
	zs_register_shrinker(pool);

	return pool;

err:
	zs_destroy_pool(pool);
	return NULL;
}