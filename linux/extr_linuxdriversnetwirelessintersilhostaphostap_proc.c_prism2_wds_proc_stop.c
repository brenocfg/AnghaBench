#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int /*<<< orphan*/  file; } ;
struct TYPE_3__ {int /*<<< orphan*/  iface_lock; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 TYPE_1__* PDE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prism2_wds_proc_stop(struct seq_file *m, void *v)
{
	local_info_t *local = PDE_DATA(file_inode(m->file));
	read_unlock_bh(&local->iface_lock);
}