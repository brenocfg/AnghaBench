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
struct track {int dummy; } ;
struct kmem_cache {int flags; unsigned int object_size; unsigned int inuse; unsigned int offset; int red_left_pad; int align; unsigned int size; void* oo; void* max; void* min; int /*<<< orphan*/  allocflags; scalar_t__ ctor; } ;
typedef  int slab_flags_t ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 int /*<<< orphan*/  GFP_DMA ; 
 int /*<<< orphan*/  GFP_DMA32 ; 
 int SLAB_CACHE_DMA ; 
 int SLAB_CACHE_DMA32 ; 
 int SLAB_POISON ; 
 int SLAB_RECLAIM_ACCOUNT ; 
 int SLAB_RED_ZONE ; 
 int SLAB_STORE_USER ; 
 int SLAB_TYPESAFE_BY_RCU ; 
 int /*<<< orphan*/  __GFP_COMP ; 
 int /*<<< orphan*/  __GFP_RECLAIMABLE ; 
 int __OBJECT_POISON ; 
 unsigned int calculate_order (unsigned int) ; 
 unsigned int get_order (unsigned int) ; 
 int /*<<< orphan*/  kasan_cache_create (struct kmem_cache*,unsigned int*,int*) ; 
 void* oo_make (unsigned int,unsigned int) ; 
 scalar_t__ oo_objects (void*) ; 

__attribute__((used)) static int calculate_sizes(struct kmem_cache *s, int forced_order)
{
	slab_flags_t flags = s->flags;
	unsigned int size = s->object_size;
	unsigned int order;

	/*
	 * Round up object size to the next word boundary. We can only
	 * place the free pointer at word boundaries and this determines
	 * the possible location of the free pointer.
	 */
	size = ALIGN(size, sizeof(void *));

#ifdef CONFIG_SLUB_DEBUG
	/*
	 * Determine if we can poison the object itself. If the user of
	 * the slab may touch the object after free or before allocation
	 * then we should never poison the object itself.
	 */
	if ((flags & SLAB_POISON) && !(flags & SLAB_TYPESAFE_BY_RCU) &&
			!s->ctor)
		s->flags |= __OBJECT_POISON;
	else
		s->flags &= ~__OBJECT_POISON;


	/*
	 * If we are Redzoning then check if there is some space between the
	 * end of the object and the free pointer. If not then add an
	 * additional word to have some bytes to store Redzone information.
	 */
	if ((flags & SLAB_RED_ZONE) && size == s->object_size)
		size += sizeof(void *);
#endif

	/*
	 * With that we have determined the number of bytes in actual use
	 * by the object. This is the potential offset to the free pointer.
	 */
	s->inuse = size;

	if (((flags & (SLAB_TYPESAFE_BY_RCU | SLAB_POISON)) ||
		s->ctor)) {
		/*
		 * Relocate free pointer after the object if it is not
		 * permitted to overwrite the first word of the object on
		 * kmem_cache_free.
		 *
		 * This is the case if we do RCU, have a constructor or
		 * destructor or are poisoning the objects.
		 */
		s->offset = size;
		size += sizeof(void *);
	}

#ifdef CONFIG_SLUB_DEBUG
	if (flags & SLAB_STORE_USER)
		/*
		 * Need to store information about allocs and frees after
		 * the object.
		 */
		size += 2 * sizeof(struct track);
#endif

	kasan_cache_create(s, &size, &s->flags);
#ifdef CONFIG_SLUB_DEBUG
	if (flags & SLAB_RED_ZONE) {
		/*
		 * Add some empty padding so that we can catch
		 * overwrites from earlier objects rather than let
		 * tracking information or the free pointer be
		 * corrupted if a user writes before the start
		 * of the object.
		 */
		size += sizeof(void *);

		s->red_left_pad = sizeof(void *);
		s->red_left_pad = ALIGN(s->red_left_pad, s->align);
		size += s->red_left_pad;
	}
#endif

	/*
	 * SLUB stores one object immediately after another beginning from
	 * offset 0. In order to align the objects we have to simply size
	 * each object to conform to the alignment.
	 */
	size = ALIGN(size, s->align);
	s->size = size;
	if (forced_order >= 0)
		order = forced_order;
	else
		order = calculate_order(size);

	if ((int)order < 0)
		return 0;

	s->allocflags = 0;
	if (order)
		s->allocflags |= __GFP_COMP;

	if (s->flags & SLAB_CACHE_DMA)
		s->allocflags |= GFP_DMA;

	if (s->flags & SLAB_CACHE_DMA32)
		s->allocflags |= GFP_DMA32;

	if (s->flags & SLAB_RECLAIM_ACCOUNT)
		s->allocflags |= __GFP_RECLAIMABLE;

	/*
	 * Determine the number of objects per slab
	 */
	s->oo = oo_make(order, size);
	s->min = oo_make(get_order(size), size);
	if (oo_objects(s->oo) > oo_objects(s->max))
		s->max = s->oo;

	return !!oo_objects(s->oo);
}