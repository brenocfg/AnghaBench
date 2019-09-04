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
struct dasd_block {int /*<<< orphan*/ * request_queue; int /*<<< orphan*/  tag_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_free_queue(struct dasd_block *block)
{
	if (block->request_queue) {
		blk_cleanup_queue(block->request_queue);
		blk_mq_free_tag_set(&block->tag_set);
		block->request_queue = NULL;
	}
}