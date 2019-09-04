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
struct seq_file {int /*<<< orphan*/  file; } ;
struct ap_data {int /*<<< orphan*/  sta_list; int /*<<< orphan*/  sta_table_lock; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct ap_data* PDE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (int /*<<< orphan*/ ) ; 
 void* seq_list_start_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *prism2_ap_proc_start(struct seq_file *m, loff_t *_pos)
{
	struct ap_data *ap = PDE_DATA(file_inode(m->file));
	spin_lock_bh(&ap->sta_table_lock);
	return seq_list_start_head(&ap->sta_list, *_pos);
}