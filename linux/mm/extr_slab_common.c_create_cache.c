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
struct mem_cgroup {int dummy; } ;
struct kmem_cache {char const* name; unsigned int size; unsigned int object_size; unsigned int align; void (* ctor ) (void*) ;unsigned int useroffset; unsigned int usersize; int refcount; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  slab_flags_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct kmem_cache* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int __kmem_cache_create (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_memcg_params (struct kmem_cache*) ; 
 int init_memcg_params (struct kmem_cache*,struct kmem_cache*) ; 
 int /*<<< orphan*/  kmem_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kmem_cache*) ; 
 struct kmem_cache* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcg_link_cache (struct kmem_cache*,struct mem_cgroup*) ; 
 int /*<<< orphan*/  slab_caches ; 

__attribute__((used)) static struct kmem_cache *create_cache(const char *name,
		unsigned int object_size, unsigned int align,
		slab_flags_t flags, unsigned int useroffset,
		unsigned int usersize, void (*ctor)(void *),
		struct mem_cgroup *memcg, struct kmem_cache *root_cache)
{
	struct kmem_cache *s;
	int err;

	if (WARN_ON(useroffset + usersize > object_size))
		useroffset = usersize = 0;

	err = -ENOMEM;
	s = kmem_cache_zalloc(kmem_cache, GFP_KERNEL);
	if (!s)
		goto out;

	s->name = name;
	s->size = s->object_size = object_size;
	s->align = align;
	s->ctor = ctor;
	s->useroffset = useroffset;
	s->usersize = usersize;

	err = init_memcg_params(s, root_cache);
	if (err)
		goto out_free_cache;

	err = __kmem_cache_create(s, flags);
	if (err)
		goto out_free_cache;

	s->refcount = 1;
	list_add(&s->list, &slab_caches);
	memcg_link_cache(s, memcg);
out:
	if (err)
		return ERR_PTR(err);
	return s;

out_free_cache:
	destroy_memcg_params(s);
	kmem_cache_free(kmem_cache, s);
	goto out;
}