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
struct pid_namespace {struct pid_namespace* parent; } ;
struct bsd_acct_struct {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct bsd_acct_struct* acct_get (struct pid_namespace*) ; 
 int /*<<< orphan*/  acct_put (struct bsd_acct_struct*) ; 
 int /*<<< orphan*/  do_acct_process (struct bsd_acct_struct*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void slow_acct_process(struct pid_namespace *ns)
{
	for ( ; ns; ns = ns->parent) {
		struct bsd_acct_struct *acct = acct_get(ns);
		if (acct) {
			do_acct_process(acct);
			mutex_unlock(&acct->lock);
			acct_put(acct);
		}
	}
}