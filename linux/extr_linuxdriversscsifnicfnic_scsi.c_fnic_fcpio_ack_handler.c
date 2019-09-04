#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnic_wq_copy {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  ack_index_out_of_range; int /*<<< orphan*/  last_ack_time; } ;
struct TYPE_10__ {TYPE_3__ misc_stats; } ;
struct fnic {unsigned int raw_wq_count; unsigned int rq_count; int* fw_ack_recd; TYPE_6__* lport; int /*<<< orphan*/ * wq_copy_lock; TYPE_4__ fnic_stats; int /*<<< orphan*/ * fw_ack_index; struct vnic_wq_copy* wq_copy; } ;
struct TYPE_7__ {int /*<<< orphan*/  request_out; } ;
struct TYPE_8__ {TYPE_1__ ack; } ;
struct fcpio_fw_req {TYPE_2__ u; } ;
struct TYPE_12__ {TYPE_5__* host; } ;
struct TYPE_11__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNIC_TRACE (void (*) (struct fnic*,unsigned int,struct fcpio_fw_req*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ is_ack_index_in_range (struct vnic_wq_copy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void fnic_fcpio_ack_handler(struct fnic *fnic,
					  unsigned int cq_index,
					  struct fcpio_fw_req *desc)
{
	struct vnic_wq_copy *wq;
	u16 request_out = desc->u.ack.request_out;
	unsigned long flags;
	u64 *ox_id_tag = (u64 *)(void *)desc;

	/* mark the ack state */
	wq = &fnic->wq_copy[cq_index - fnic->raw_wq_count - fnic->rq_count];
	spin_lock_irqsave(&fnic->wq_copy_lock[0], flags);

	fnic->fnic_stats.misc_stats.last_ack_time = jiffies;
	if (is_ack_index_in_range(wq, request_out)) {
		fnic->fw_ack_index[0] = request_out;
		fnic->fw_ack_recd[0] = 1;
	} else
		atomic64_inc(
			&fnic->fnic_stats.misc_stats.ack_index_out_of_range);

	spin_unlock_irqrestore(&fnic->wq_copy_lock[0], flags);
	FNIC_TRACE(fnic_fcpio_ack_handler,
		  fnic->lport->host->host_no, 0, 0, ox_id_tag[2], ox_id_tag[3],
		  ox_id_tag[4], ox_id_tag[5]);
}