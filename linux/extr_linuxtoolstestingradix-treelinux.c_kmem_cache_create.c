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
struct kmem_cache {size_t size; void (* ctor ) (void*) ;int /*<<< orphan*/ * objs; scalar_t__ nr_objs; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct kmem_cache* malloc (int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct kmem_cache *
kmem_cache_create(const char *name, size_t size, size_t offset,
	unsigned long flags, void (*ctor)(void *))
{
	struct kmem_cache *ret = malloc(sizeof(*ret));

	pthread_mutex_init(&ret->lock, NULL);
	ret->size = size;
	ret->nr_objs = 0;
	ret->objs = NULL;
	ret->ctor = ctor;
	return ret;
}