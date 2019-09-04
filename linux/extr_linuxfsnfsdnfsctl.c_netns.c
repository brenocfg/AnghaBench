#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* i_sb; } ;
struct TYPE_3__ {struct net* s_fs_info; } ;

/* Variables and functions */
 TYPE_2__* file_inode (struct file*) ; 

__attribute__((used)) static inline struct net *netns(struct file *file)
{
	return file_inode(file)->i_sb->s_fs_info;
}