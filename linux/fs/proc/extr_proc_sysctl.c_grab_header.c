#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct ctl_table_header {int dummy; } ;
struct TYPE_8__ {struct ctl_table_header* sysctl; } ;
struct TYPE_5__ {struct ctl_table_header header; } ;
struct TYPE_6__ {TYPE_1__ dir; } ;
struct TYPE_7__ {TYPE_2__ default_set; } ;

/* Variables and functions */
 TYPE_4__* PROC_I (struct inode*) ; 
 struct ctl_table_header* sysctl_head_grab (struct ctl_table_header*) ; 
 TYPE_3__ sysctl_table_root ; 

__attribute__((used)) static struct ctl_table_header *grab_header(struct inode *inode)
{
	struct ctl_table_header *head = PROC_I(inode)->sysctl;
	if (!head)
		head = &sysctl_table_root.default_set.dir.header;
	return sysctl_head_grab(head);
}