#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int count; unsigned int nr_segs; } ;
struct msghdr {TYPE_1__ msg_iter; } ;
struct bio_vec {int /*<<< orphan*/  bv_page; } ;
struct afs_call {scalar_t__ first; scalar_t__ last; unsigned int first_offset; int /*<<< orphan*/  rxcall; TYPE_2__* net; } ;
typedef  scalar_t__ pgoff_t ;
struct TYPE_4__ {int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int AFS_BVEC_MAX ; 
 int /*<<< orphan*/  afs_load_bvec (struct afs_call*,struct msghdr*,struct bio_vec*,scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  afs_notify_end_request_tx ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int rxrpc_kernel_send_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msghdr*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_send_pages (struct afs_call*,struct msghdr*,scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  trace_afs_sent_pages (struct afs_call*,scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int afs_send_pages(struct afs_call *call, struct msghdr *msg)
{
	struct bio_vec bv[AFS_BVEC_MAX];
	unsigned int bytes, nr, loop, offset;
	pgoff_t first = call->first, last = call->last;
	int ret;

	offset = call->first_offset;
	call->first_offset = 0;

	do {
		afs_load_bvec(call, msg, bv, first, last, offset);
		trace_afs_send_pages(call, msg, first, last, offset);

		offset = 0;
		bytes = msg->msg_iter.count;
		nr = msg->msg_iter.nr_segs;

		ret = rxrpc_kernel_send_data(call->net->socket, call->rxcall, msg,
					     bytes, afs_notify_end_request_tx);
		for (loop = 0; loop < nr; loop++)
			put_page(bv[loop].bv_page);
		if (ret < 0)
			break;

		first += nr;
	} while (first <= last);

	trace_afs_sent_pages(call, call->first, last, first, ret);
	return ret;
}