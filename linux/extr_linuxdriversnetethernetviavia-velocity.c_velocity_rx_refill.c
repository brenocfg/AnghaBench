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
struct TYPE_8__ {int dirty; int curr; int filled; TYPE_2__* info; struct rx_desc* ring; } ;
struct TYPE_7__ {int numrx; } ;
struct velocity_info {TYPE_4__ rx; TYPE_3__ options; } ;
struct TYPE_5__ {int len; } ;
struct rx_desc {TYPE_1__ rdesc0; } ;
struct TYPE_6__ {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int OWNED_BY_NIC ; 
 scalar_t__ velocity_alloc_rx_buf (struct velocity_info*,int) ; 

__attribute__((used)) static int velocity_rx_refill(struct velocity_info *vptr)
{
	int dirty = vptr->rx.dirty, done = 0;

	do {
		struct rx_desc *rd = vptr->rx.ring + dirty;

		/* Fine for an all zero Rx desc at init time as well */
		if (rd->rdesc0.len & OWNED_BY_NIC)
			break;

		if (!vptr->rx.info[dirty].skb) {
			if (velocity_alloc_rx_buf(vptr, dirty) < 0)
				break;
		}
		done++;
		dirty = (dirty < vptr->options.numrx - 1) ? dirty + 1 : 0;
	} while (dirty != vptr->rx.curr);

	if (done) {
		vptr->rx.dirty = dirty;
		vptr->rx.filled += done;
	}

	return done;
}