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
 int /*<<< orphan*/  atm_dev_mutex ; 
 int /*<<< orphan*/  atm_devs ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 void* seq_list_start_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *atm_dev_seq_start(struct seq_file *seq, loff_t *pos)
{
	mutex_lock(&atm_dev_mutex);
	return seq_list_start_head(&atm_devs, *pos);
}