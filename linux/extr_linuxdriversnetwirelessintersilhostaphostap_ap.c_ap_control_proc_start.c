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
struct seq_file {int /*<<< orphan*/  file; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_list; int /*<<< orphan*/  lock; } ;
struct ap_data {TYPE_1__ mac_restrictions; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct ap_data* PDE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (int /*<<< orphan*/ ) ; 
 void* seq_list_start_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *ap_control_proc_start(struct seq_file *m, loff_t *_pos)
{
	struct ap_data *ap = PDE_DATA(file_inode(m->file));
	spin_lock_bh(&ap->mac_restrictions.lock);
	return seq_list_start_head(&ap->mac_restrictions.mac_list, *_pos);
}