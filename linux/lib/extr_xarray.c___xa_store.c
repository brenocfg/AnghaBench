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
struct xarray {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 void* XA_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XA_FREE_MARK ; 
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,struct xarray*,unsigned long) ; 
 void* XA_ZERO_ENTRY ; 
 scalar_t__ __xas_nomem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_is_advanced (void*) ; 
 scalar_t__ xa_track_free (struct xarray*) ; 
 int /*<<< orphan*/  xas ; 
 int /*<<< orphan*/  xas_clear_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* xas_result (int /*<<< orphan*/ *,void*) ; 
 void* xas_store (int /*<<< orphan*/ *,void*) ; 

void *__xa_store(struct xarray *xa, unsigned long index, void *entry, gfp_t gfp)
{
	XA_STATE(xas, xa, index);
	void *curr;

	if (WARN_ON_ONCE(xa_is_advanced(entry)))
		return XA_ERROR(-EINVAL);
	if (xa_track_free(xa) && !entry)
		entry = XA_ZERO_ENTRY;

	do {
		curr = xas_store(&xas, entry);
		if (xa_track_free(xa))
			xas_clear_mark(&xas, XA_FREE_MARK);
	} while (__xas_nomem(&xas, gfp));

	return xas_result(&xas, curr);
}