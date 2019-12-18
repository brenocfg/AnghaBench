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
struct btrfsic_stack_frame {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFSIC_BLOCK_STACK_FRAME_MAGIC_NUMBER ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct btrfsic_stack_frame* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static struct btrfsic_stack_frame *btrfsic_stack_frame_alloc(void)
{
	struct btrfsic_stack_frame *sf;

	sf = kzalloc(sizeof(*sf), GFP_NOFS);
	if (NULL == sf)
		pr_info("btrfsic: alloc memory failed!\n");
	else
		sf->magic = BTRFSIC_BLOCK_STACK_FRAME_MAGIC_NUMBER;
	return sf;
}