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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __raw_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int expect_close ; 
 TYPE_1__ ident ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbwdog_gate ; 
 int /*<<< orphan*/  sbwdog_pet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_dog ; 

__attribute__((used)) static int sbwdog_release(struct inode *inode, struct file *file)
{
	if (expect_close == 42) {
		__raw_writeb(0, user_dog);
		module_put(THIS_MODULE);
	} else {
		pr_crit("%s: Unexpected close, not stopping watchdog!\n",
			ident.identity);
		sbwdog_pet(user_dog);
	}
	clear_bit(0, &sbwdog_gate);
	expect_close = 0;

	return 0;
}