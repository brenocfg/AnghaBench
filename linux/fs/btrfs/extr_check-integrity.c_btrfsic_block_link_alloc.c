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
struct btrfsic_block_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  btrfsic_block_link_init (struct btrfsic_block_link*) ; 
 struct btrfsic_block_link* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct btrfsic_block_link *btrfsic_block_link_alloc(void)
{
	struct btrfsic_block_link *l;

	l = kzalloc(sizeof(*l), GFP_NOFS);
	if (NULL != l)
		btrfsic_block_link_init(l);

	return l;
}