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
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 void* seq_list_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprobe_list ; 
 int /*<<< orphan*/  uprobe_lock ; 

__attribute__((used)) static void *probes_seq_start(struct seq_file *m, loff_t *pos)
{
	mutex_lock(&uprobe_lock);
	return seq_list_start(&uprobe_list, *pos);
}