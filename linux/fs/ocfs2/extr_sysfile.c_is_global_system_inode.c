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

/* Variables and functions */
 int OCFS2_FIRST_ONLINE_SYSTEM_INODE ; 
 int OCFS2_LAST_GLOBAL_SYSTEM_INODE ; 

__attribute__((used)) static inline int is_global_system_inode(int type)
{
	return type >= OCFS2_FIRST_ONLINE_SYSTEM_INODE &&
		type <= OCFS2_LAST_GLOBAL_SYSTEM_INODE;
}