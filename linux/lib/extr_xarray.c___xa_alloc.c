#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xarray {int dummy; } ;
struct xa_limit {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_9__ {scalar_t__ xa_node; int /*<<< orphan*/  xa_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int EINVAL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ XAS_RESTART ; 
 int /*<<< orphan*/  XA_FREE_MARK ; 
 int /*<<< orphan*/  XA_STATE (TYPE_1__,struct xarray*,int /*<<< orphan*/ ) ; 
 void* XA_ZERO_ENTRY ; 
 scalar_t__ __xas_nomem (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int xa_is_advanced (void*) ; 
 int /*<<< orphan*/  xa_track_free (struct xarray*) ; 
 TYPE_1__ xas ; 
 int /*<<< orphan*/  xas_clear_mark (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int xas_error (TYPE_1__*) ; 
 int /*<<< orphan*/  xas_find_marked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_set_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_store (TYPE_1__*,void*) ; 

int __xa_alloc(struct xarray *xa, u32 *id, void *entry,
		struct xa_limit limit, gfp_t gfp)
{
	XA_STATE(xas, xa, 0);

	if (WARN_ON_ONCE(xa_is_advanced(entry)))
		return -EINVAL;
	if (WARN_ON_ONCE(!xa_track_free(xa)))
		return -EINVAL;

	if (!entry)
		entry = XA_ZERO_ENTRY;

	do {
		xas.xa_index = limit.min;
		xas_find_marked(&xas, limit.max, XA_FREE_MARK);
		if (xas.xa_node == XAS_RESTART)
			xas_set_err(&xas, -EBUSY);
		else
			*id = xas.xa_index;
		xas_store(&xas, entry);
		xas_clear_mark(&xas, XA_FREE_MARK);
	} while (__xas_nomem(&xas, gfp));

	return xas_error(&xas);
}