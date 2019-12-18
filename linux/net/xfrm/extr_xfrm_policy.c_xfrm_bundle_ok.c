#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct dst_entry {int flags; TYPE_4__* xfrm; scalar_t__ dev; } ;
struct TYPE_7__ {struct dst_entry dst; } ;
struct xfrm_dst {scalar_t__ xfrm_genid; scalar_t__ num_pols; scalar_t__ policy_genid; scalar_t__ child_mtu_cached; scalar_t__ route_mtu_cached; TYPE_3__ u; struct dst_entry* route; int /*<<< orphan*/  route_cookie; TYPE_2__** pols; int /*<<< orphan*/  path_cookie; } ;
struct TYPE_5__ {scalar_t__ state; } ;
struct TYPE_8__ {scalar_t__ genid; TYPE_1__ km; } ;
struct TYPE_6__ {int /*<<< orphan*/  genid; } ;

/* Variables and functions */
 int DST_XFRM_QUEUE ; 
 int /*<<< orphan*/  RTAX_MTU ; 
 int XFRM_MAX_DEPTH ; 
 scalar_t__ XFRM_STATE_VALID ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_check (struct dst_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_metric_set (struct dst_entry*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dst_mtu (struct dst_entry*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netif_running (scalar_t__) ; 
 struct dst_entry* xfrm_dst_child (struct dst_entry*) ; 
 struct dst_entry* xfrm_dst_path (struct dst_entry*) ; 
 scalar_t__ xfrm_state_mtu (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int xfrm_bundle_ok(struct xfrm_dst *first)
{
	struct xfrm_dst *bundle[XFRM_MAX_DEPTH];
	struct dst_entry *dst = &first->u.dst;
	struct xfrm_dst *xdst;
	int start_from, nr;
	u32 mtu;

	if (!dst_check(xfrm_dst_path(dst), ((struct xfrm_dst *)dst)->path_cookie) ||
	    (dst->dev && !netif_running(dst->dev)))
		return 0;

	if (dst->flags & DST_XFRM_QUEUE)
		return 1;

	start_from = nr = 0;
	do {
		struct xfrm_dst *xdst = (struct xfrm_dst *)dst;

		if (dst->xfrm->km.state != XFRM_STATE_VALID)
			return 0;
		if (xdst->xfrm_genid != dst->xfrm->genid)
			return 0;
		if (xdst->num_pols > 0 &&
		    xdst->policy_genid != atomic_read(&xdst->pols[0]->genid))
			return 0;

		bundle[nr++] = xdst;

		mtu = dst_mtu(xfrm_dst_child(dst));
		if (xdst->child_mtu_cached != mtu) {
			start_from = nr;
			xdst->child_mtu_cached = mtu;
		}

		if (!dst_check(xdst->route, xdst->route_cookie))
			return 0;
		mtu = dst_mtu(xdst->route);
		if (xdst->route_mtu_cached != mtu) {
			start_from = nr;
			xdst->route_mtu_cached = mtu;
		}

		dst = xfrm_dst_child(dst);
	} while (dst->xfrm);

	if (likely(!start_from))
		return 1;

	xdst = bundle[start_from - 1];
	mtu = xdst->child_mtu_cached;
	while (start_from--) {
		dst = &xdst->u.dst;

		mtu = xfrm_state_mtu(dst->xfrm, mtu);
		if (mtu > xdst->route_mtu_cached)
			mtu = xdst->route_mtu_cached;
		dst_metric_set(dst, RTAX_MTU, mtu);
		if (!start_from)
			break;

		xdst = bundle[start_from - 1];
		xdst->child_mtu_cached = mtu;
	}

	return 1;
}