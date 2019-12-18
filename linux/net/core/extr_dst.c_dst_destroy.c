#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfrm_dst {struct dst_entry* child; } ;
struct metadata_dst {int dummy; } ;
struct dst_entry {int flags; TYPE_1__* ops; int /*<<< orphan*/  lwtstate; scalar_t__ dev; scalar_t__ xfrm; } ;
struct TYPE_2__ {int /*<<< orphan*/  kmem_cachep; int /*<<< orphan*/  (* destroy ) (struct dst_entry*) ;} ;

/* Variables and functions */
 int DST_METADATA ; 
 int DST_NOCOUNT ; 
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 int /*<<< orphan*/  dst_entries_add (TYPE_1__*,int) ; 
 int /*<<< orphan*/  dst_release_immediate (struct dst_entry*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dst_entry*) ; 
 int /*<<< orphan*/  lwtstate_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_dst_free (struct metadata_dst*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  stub1 (struct dst_entry*) ; 

struct dst_entry *dst_destroy(struct dst_entry * dst)
{
	struct dst_entry *child = NULL;

	smp_rmb();

#ifdef CONFIG_XFRM
	if (dst->xfrm) {
		struct xfrm_dst *xdst = (struct xfrm_dst *) dst;

		child = xdst->child;
	}
#endif
	if (!(dst->flags & DST_NOCOUNT))
		dst_entries_add(dst->ops, -1);

	if (dst->ops->destroy)
		dst->ops->destroy(dst);
	if (dst->dev)
		dev_put(dst->dev);

	lwtstate_put(dst->lwtstate);

	if (dst->flags & DST_METADATA)
		metadata_dst_free((struct metadata_dst *)dst);
	else
		kmem_cache_free(dst->ops->kmem_cachep, dst);

	dst = child;
	if (dst)
		dst_release_immediate(dst);
	return NULL;
}