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
typedef  size_t u32 ;
struct brcmf_msgbuf {int /*<<< orphan*/  txflow_work; int /*<<< orphan*/  txflow_wq; struct brcmf_commonring** flowrings; int /*<<< orphan*/  flow_map; } ;
struct brcmf_commonring {int /*<<< orphan*/  outstanding_tx; } ;

/* Variables and functions */
 scalar_t__ BRCMF_MSGBUF_DELAY_TXWORKER_THRS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_msgbuf_schedule_txdata(struct brcmf_msgbuf *msgbuf, u32 flowid,
					bool force)
{
	struct brcmf_commonring *commonring;

	set_bit(flowid, msgbuf->flow_map);
	commonring = msgbuf->flowrings[flowid];
	if ((force) || (atomic_read(&commonring->outstanding_tx) <
			BRCMF_MSGBUF_DELAY_TXWORKER_THRS))
		queue_work(msgbuf->txflow_wq, &msgbuf->txflow_work);

	return 0;
}