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

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_object (void*) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  scan_mutex ; 

__attribute__((used)) static void kmemleak_seq_stop(struct seq_file *seq, void *v)
{
	if (!IS_ERR(v)) {
		/*
		 * kmemleak_seq_start may return ERR_PTR if the scan_mutex
		 * waiting was interrupted, so only release it if !IS_ERR.
		 */
		rcu_read_unlock();
		mutex_unlock(&scan_mutex);
		if (v)
			put_object(v);
	}
}