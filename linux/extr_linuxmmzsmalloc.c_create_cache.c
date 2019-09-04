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
struct zspage {int dummy; } ;
struct zs_pool {int /*<<< orphan*/ * handle_cachep; void* zspage_cachep; } ;

/* Variables and functions */
 int ZS_HANDLE_SIZE ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_cache(struct zs_pool *pool)
{
	pool->handle_cachep = kmem_cache_create("zs_handle", ZS_HANDLE_SIZE,
					0, 0, NULL);
	if (!pool->handle_cachep)
		return 1;

	pool->zspage_cachep = kmem_cache_create("zspage", sizeof(struct zspage),
					0, 0, NULL);
	if (!pool->zspage_cachep) {
		kmem_cache_destroy(pool->handle_cachep);
		pool->handle_cachep = NULL;
		return 1;
	}

	return 0;
}