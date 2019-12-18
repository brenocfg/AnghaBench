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
struct fib_info {scalar_t__ fib_dead; int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib_info_cnt ; 
 int /*<<< orphan*/  free_fib_info_rcu ; 
 int /*<<< orphan*/  pr_warn (char*,struct fib_info*) ; 

void free_fib_info(struct fib_info *fi)
{
	if (fi->fib_dead == 0) {
		pr_warn("Freeing alive fib_info %p\n", fi);
		return;
	}
	fib_info_cnt--;

	call_rcu(&fi->rcu, free_fib_info_rcu);
}