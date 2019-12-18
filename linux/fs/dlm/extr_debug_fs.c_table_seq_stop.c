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
struct rsbtbl_iter {int /*<<< orphan*/  rsb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_put_rsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rsbtbl_iter*) ; 

__attribute__((used)) static void table_seq_stop(struct seq_file *seq, void *iter_ptr)
{
	struct rsbtbl_iter *ri = iter_ptr;

	if (ri) {
		dlm_put_rsb(ri->rsb);
		kfree(ri);
	}
}