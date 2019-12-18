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
struct ipc_namespace {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_fs_info; } ;

/* Variables and functions */
 struct ipc_namespace* get_ipc_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ipc_namespace *__get_ns_from_inode(struct inode *inode)
{
	return get_ipc_ns(inode->i_sb->s_fs_info);
}