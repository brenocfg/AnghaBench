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
struct array_cache {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  init_arraycache (struct array_cache*,int,int) ; 
 struct array_cache* kmalloc_node (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmemleak_no_scan (struct array_cache*) ; 

__attribute__((used)) static struct array_cache *alloc_arraycache(int node, int entries,
					    int batchcount, gfp_t gfp)
{
	size_t memsize = sizeof(void *) * entries + sizeof(struct array_cache);
	struct array_cache *ac = NULL;

	ac = kmalloc_node(memsize, gfp, node);
	/*
	 * The array_cache structures contain pointers to free object.
	 * However, when such objects are allocated or transferred to another
	 * cache the pointers are not cleared and they could be counted as
	 * valid references during a kmemleak scan. Therefore, kmemleak must
	 * not scan such objects.
	 */
	kmemleak_no_scan(ac);
	init_arraycache(ac, entries, batchcount);
	return ac;
}