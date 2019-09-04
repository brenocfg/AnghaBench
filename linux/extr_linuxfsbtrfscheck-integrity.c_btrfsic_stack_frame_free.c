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
struct btrfsic_stack_frame {scalar_t__ magic; } ;

/* Variables and functions */
 scalar_t__ BTRFSIC_BLOCK_STACK_FRAME_MAGIC_NUMBER ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kfree (struct btrfsic_stack_frame*) ; 

__attribute__((used)) static void btrfsic_stack_frame_free(struct btrfsic_stack_frame *sf)
{
	BUG_ON(!(NULL == sf ||
		 BTRFSIC_BLOCK_STACK_FRAME_MAGIC_NUMBER == sf->magic));
	kfree(sf);
}