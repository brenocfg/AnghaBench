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
struct fs_pin {int dummy; } ;
struct bsd_acct_struct {int /*<<< orphan*/  lock; TYPE_1__* ns; int /*<<< orphan*/  done; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {int /*<<< orphan*/  bacct; } ;

/* Variables and functions */
 int /*<<< orphan*/  acct_put (struct bsd_acct_struct*) ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,struct fs_pin*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_acct_process (struct bsd_acct_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pin_remove (struct fs_pin*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct bsd_acct_struct* to_acct (struct fs_pin*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acct_pin_kill(struct fs_pin *pin)
{
	struct bsd_acct_struct *acct = to_acct(pin);
	mutex_lock(&acct->lock);
	do_acct_process(acct);
	schedule_work(&acct->work);
	wait_for_completion(&acct->done);
	cmpxchg(&acct->ns->bacct, pin, NULL);
	mutex_unlock(&acct->lock);
	pin_remove(pin);
	acct_put(acct);
}