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
struct net_device {int dummy; } ;
struct dst_ops {scalar_t__ gc_thresh; int /*<<< orphan*/  kmem_cachep; scalar_t__ (* gc ) (struct dst_ops*) ;} ;
typedef  void dst_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ dst_entries_get_fast (struct dst_ops*) ; 
 int /*<<< orphan*/  dst_init (void*,struct dst_ops*,struct net_device*,int,int,unsigned short) ; 
 void* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dst_ops*) ; 

void *dst_alloc(struct dst_ops *ops, struct net_device *dev,
		int initial_ref, int initial_obsolete, unsigned short flags)
{
	struct dst_entry *dst;

	if (ops->gc && dst_entries_get_fast(ops) > ops->gc_thresh) {
		if (ops->gc(ops))
			return NULL;
	}

	dst = kmem_cache_alloc(ops->kmem_cachep, GFP_ATOMIC);
	if (!dst)
		return NULL;

	dst_init(dst, ops, dev, initial_ref, initial_obsolete, flags);

	return dst;
}