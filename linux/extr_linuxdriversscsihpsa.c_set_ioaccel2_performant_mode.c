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
struct io_accel2_cmd {int reply_queue; size_t sg_count; } ;
struct ctlr_info {int /*<<< orphan*/ * ioaccel2_blockFetchTable; struct io_accel2_cmd* ioaccel2_cmd_pool; } ;
struct CommandList {size_t cmdindex; int /*<<< orphan*/  busaddr; } ;

/* Variables and functions */

__attribute__((used)) static void set_ioaccel2_performant_mode(struct ctlr_info *h,
						struct CommandList *c,
						int reply_queue)
{
	struct io_accel2_cmd *cp = &h->ioaccel2_cmd_pool[c->cmdindex];

	/*
	 * Tell the controller to post the reply to the queue for this
	 * processor.  This seems to give the best I/O throughput.
	 */
	cp->reply_queue = reply_queue;
	/*
	 * Set the bits in the address sent down to include:
	 *  - performant mode bit not used in ioaccel mode 2
	 *  - pull count (bits 0-3)
	 *  - command type isn't needed for ioaccel2
	 */
	c->busaddr |= (h->ioaccel2_blockFetchTable[cp->sg_count]);
}