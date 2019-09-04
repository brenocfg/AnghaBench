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
struct io_accel1_cmd {int ReplyQueue; } ;
struct ctlr_info {int* ioaccel1_blockFetchTable; struct io_accel1_cmd* ioaccel_cmd_pool; } ;
struct TYPE_2__ {size_t SGList; } ;
struct CommandList {size_t cmdindex; int busaddr; TYPE_1__ Header; } ;

/* Variables and functions */
 int IOACCEL1_BUSADDR_CMDTYPE ; 

__attribute__((used)) static void set_ioaccel1_performant_mode(struct ctlr_info *h,
						struct CommandList *c,
						int reply_queue)
{
	struct io_accel1_cmd *cp = &h->ioaccel_cmd_pool[c->cmdindex];

	/*
	 * Tell the controller to post the reply to the queue for this
	 * processor.  This seems to give the best I/O throughput.
	 */
	cp->ReplyQueue = reply_queue;
	/*
	 * Set the bits in the address sent down to include:
	 *  - performant mode bit (bit 0)
	 *  - pull count (bits 1-3)
	 *  - command type (bits 4-6)
	 */
	c->busaddr |= 1 | (h->ioaccel1_blockFetchTable[c->Header.SGList] << 1) |
					IOACCEL1_BUSADDR_CMDTYPE;
}