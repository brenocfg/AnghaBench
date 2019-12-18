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
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* tasks; } ;
struct TYPE_3__ {int /*<<< orphan*/  first; } ;

/* Variables and functions */
 size_t PIDTYPE_PID ; 
 TYPE_2__* proc_pid (struct inode*) ; 

__attribute__((used)) static inline bool proc_inode_is_dead(struct inode *inode)
{
	return !proc_pid(inode)->tasks[PIDTYPE_PID].first;
}