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
struct fscache_cookie_def {int /*<<< orphan*/  type; } ;
struct fscache_cookie {size_t key_len; size_t aux_len; int flags; int /*<<< orphan*/  stores; int /*<<< orphan*/  backing_objects; int /*<<< orphan*/  stores_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  type; void* netfs_data; struct fscache_cookie* parent; struct fscache_cookie_def const* def; int /*<<< orphan*/  n_active; int /*<<< orphan*/  n_children; int /*<<< orphan*/  usage; int /*<<< orphan*/  aux; int /*<<< orphan*/  inline_aux; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int FSCACHE_COOKIE_NO_DATA_YET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GFP_NOFS ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int) ; 
 int __GFP_DIRECT_RECLAIM ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fscache_cookie_jar ; 
 int /*<<< orphan*/  fscache_free_cookie (struct fscache_cookie*) ; 
 scalar_t__ fscache_set_key (struct fscache_cookie*,void const*,size_t) ; 
 struct fscache_cookie* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemdup (void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct fscache_cookie *fscache_alloc_cookie(
	struct fscache_cookie *parent,
	const struct fscache_cookie_def *def,
	const void *index_key, size_t index_key_len,
	const void *aux_data, size_t aux_data_len,
	void *netfs_data,
	loff_t object_size)
{
	struct fscache_cookie *cookie;

	/* allocate and initialise a cookie */
	cookie = kmem_cache_zalloc(fscache_cookie_jar, GFP_KERNEL);
	if (!cookie)
		return NULL;

	cookie->key_len = index_key_len;
	cookie->aux_len = aux_data_len;

	if (fscache_set_key(cookie, index_key, index_key_len) < 0)
		goto nomem;

	if (cookie->aux_len <= sizeof(cookie->inline_aux)) {
		memcpy(cookie->inline_aux, aux_data, cookie->aux_len);
	} else {
		cookie->aux = kmemdup(aux_data, cookie->aux_len, GFP_KERNEL);
		if (!cookie->aux)
			goto nomem;
	}

	atomic_set(&cookie->usage, 1);
	atomic_set(&cookie->n_children, 0);

	/* We keep the active count elevated until relinquishment to prevent an
	 * attempt to wake up every time the object operations queue quiesces.
	 */
	atomic_set(&cookie->n_active, 1);

	cookie->def		= def;
	cookie->parent		= parent;
	cookie->netfs_data	= netfs_data;
	cookie->flags		= (1 << FSCACHE_COOKIE_NO_DATA_YET);
	cookie->type		= def->type;
	spin_lock_init(&cookie->lock);
	spin_lock_init(&cookie->stores_lock);
	INIT_HLIST_HEAD(&cookie->backing_objects);

	/* radix tree insertion won't use the preallocation pool unless it's
	 * told it may not wait */
	INIT_RADIX_TREE(&cookie->stores, GFP_NOFS & ~__GFP_DIRECT_RECLAIM);
	return cookie;

nomem:
	fscache_free_cookie(cookie);
	return NULL;
}