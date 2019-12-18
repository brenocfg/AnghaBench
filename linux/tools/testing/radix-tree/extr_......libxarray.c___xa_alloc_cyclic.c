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
typedef  scalar_t__ u32 ;
struct xarray {int xa_flags; } ;
struct xa_limit {scalar_t__ min; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int XA_FLAGS_ALLOC_WRAPPED ; 
 int __xa_alloc (struct xarray*,scalar_t__*,void*,struct xa_limit,int /*<<< orphan*/ ) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 

int __xa_alloc_cyclic(struct xarray *xa, u32 *id, void *entry,
		struct xa_limit limit, u32 *next, gfp_t gfp)
{
	u32 min = limit.min;
	int ret;

	limit.min = max(min, *next);
	ret = __xa_alloc(xa, id, entry, limit, gfp);
	if ((xa->xa_flags & XA_FLAGS_ALLOC_WRAPPED) && ret == 0) {
		xa->xa_flags &= ~XA_FLAGS_ALLOC_WRAPPED;
		ret = 1;
	}

	if (ret < 0 && limit.min > min) {
		limit.min = min;
		ret = __xa_alloc(xa, id, entry, limit, gfp);
		if (ret == 0)
			ret = 1;
	}

	if (ret >= 0) {
		*next = *id + 1;
		if (*next == 0)
			xa->xa_flags |= XA_FLAGS_ALLOC_WRAPPED;
	}
	return ret;
}