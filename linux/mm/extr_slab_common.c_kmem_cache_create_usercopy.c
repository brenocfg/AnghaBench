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
struct kmem_cache {int dummy; } ;
typedef  int slab_flags_t ;

/* Variables and functions */
 int CACHE_CREATE_MASK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct kmem_cache*) ; 
 int PTR_ERR (struct kmem_cache*) ; 
 int SLAB_FLAGS_PERMITTED ; 
 int SLAB_PANIC ; 
 scalar_t__ WARN_ON (int) ; 
 struct kmem_cache* __kmem_cache_alias (char const*,unsigned int,unsigned int,int,void (*) (void*)) ; 
 int /*<<< orphan*/  calculate_alignment (int,unsigned int,unsigned int) ; 
 struct kmem_cache* create_cache (char const*,unsigned int,int /*<<< orphan*/ ,int,unsigned int,unsigned int,void (*) (void*),int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  get_online_mems () ; 
 int /*<<< orphan*/  kfree_const (char const*) ; 
 int kmem_cache_sanity_check (char const*,unsigned int) ; 
 char* kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcg_get_cache_ids () ; 
 int /*<<< orphan*/  memcg_put_cache_ids () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,char const*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,int) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  put_online_mems () ; 
 int /*<<< orphan*/  slab_mutex ; 

struct kmem_cache *
kmem_cache_create_usercopy(const char *name,
		  unsigned int size, unsigned int align,
		  slab_flags_t flags,
		  unsigned int useroffset, unsigned int usersize,
		  void (*ctor)(void *))
{
	struct kmem_cache *s = NULL;
	const char *cache_name;
	int err;

	get_online_cpus();
	get_online_mems();
	memcg_get_cache_ids();

	mutex_lock(&slab_mutex);

	err = kmem_cache_sanity_check(name, size);
	if (err) {
		goto out_unlock;
	}

	/* Refuse requests with allocator specific flags */
	if (flags & ~SLAB_FLAGS_PERMITTED) {
		err = -EINVAL;
		goto out_unlock;
	}

	/*
	 * Some allocators will constraint the set of valid flags to a subset
	 * of all flags. We expect them to define CACHE_CREATE_MASK in this
	 * case, and we'll just provide them with a sanitized version of the
	 * passed flags.
	 */
	flags &= CACHE_CREATE_MASK;

	/* Fail closed on bad usersize of useroffset values. */
	if (WARN_ON(!usersize && useroffset) ||
	    WARN_ON(size < usersize || size - usersize < useroffset))
		usersize = useroffset = 0;

	if (!usersize)
		s = __kmem_cache_alias(name, size, align, flags, ctor);
	if (s)
		goto out_unlock;

	cache_name = kstrdup_const(name, GFP_KERNEL);
	if (!cache_name) {
		err = -ENOMEM;
		goto out_unlock;
	}

	s = create_cache(cache_name, size,
			 calculate_alignment(flags, align, size),
			 flags, useroffset, usersize, ctor, NULL, NULL);
	if (IS_ERR(s)) {
		err = PTR_ERR(s);
		kfree_const(cache_name);
	}

out_unlock:
	mutex_unlock(&slab_mutex);

	memcg_put_cache_ids();
	put_online_mems();
	put_online_cpus();

	if (err) {
		if (flags & SLAB_PANIC)
			panic("kmem_cache_create: Failed to create slab '%s'. Error %d\n",
				name, err);
		else {
			pr_warn("kmem_cache_create(%s) failed with error %d\n",
				name, err);
			dump_stack();
		}
		return NULL;
	}
	return s;
}