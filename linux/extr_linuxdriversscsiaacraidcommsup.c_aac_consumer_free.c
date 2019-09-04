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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * consumer; int /*<<< orphan*/ * producer; } ;
struct aac_queue {scalar_t__ entries; TYPE_1__ headers; } ;
struct aac_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int HostNormCmdNotFull ; 
#define  HostNormCmdQueue 129 
 int HostNormRespNotFull ; 
#define  HostNormRespQueue 128 
 int /*<<< orphan*/  aac_adapter_notify (struct aac_dev*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

void aac_consumer_free(struct aac_dev * dev, struct aac_queue *q, u32 qid)
{
	int wasfull = 0;
	u32 notify;

	if ((le32_to_cpu(*q->headers.producer)+1) == le32_to_cpu(*q->headers.consumer))
		wasfull = 1;

	if (le32_to_cpu(*q->headers.consumer) >= q->entries)
		*q->headers.consumer = cpu_to_le32(1);
	else
		le32_add_cpu(q->headers.consumer, 1);

	if (wasfull) {
		switch (qid) {

		case HostNormCmdQueue:
			notify = HostNormCmdNotFull;
			break;
		case HostNormRespQueue:
			notify = HostNormRespNotFull;
			break;
		default:
			BUG();
			return;
		}
		aac_adapter_notify(dev, notify);
	}
}