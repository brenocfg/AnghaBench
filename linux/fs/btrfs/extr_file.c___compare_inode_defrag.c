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
struct inode_defrag {scalar_t__ root; scalar_t__ ino; } ;

/* Variables and functions */

__attribute__((used)) static int __compare_inode_defrag(struct inode_defrag *defrag1,
				  struct inode_defrag *defrag2)
{
	if (defrag1->root > defrag2->root)
		return 1;
	else if (defrag1->root < defrag2->root)
		return -1;
	else if (defrag1->ino > defrag2->ino)
		return 1;
	else if (defrag1->ino < defrag2->ino)
		return -1;
	else
		return 0;
}