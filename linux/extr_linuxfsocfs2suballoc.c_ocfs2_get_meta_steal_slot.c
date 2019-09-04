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
struct ocfs2_super {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_ALLOC_SYSTEM_INODE ; 
 int __ocfs2_get_steal_slot (struct ocfs2_super*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_get_meta_steal_slot(struct ocfs2_super *osb)
{
	return __ocfs2_get_steal_slot(osb, EXTENT_ALLOC_SYSTEM_INODE);
}