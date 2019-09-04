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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  sbwdog_gate ; 
 int /*<<< orphan*/  sbwdog_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  user_dog ; 

__attribute__((used)) static int sbwdog_open(struct inode *inode, struct file *file)
{
	nonseekable_open(inode, file);
	if (test_and_set_bit(0, &sbwdog_gate))
		return -EBUSY;
	__module_get(THIS_MODULE);

	/*
	 * Activate the timer
	 */
	sbwdog_set(user_dog, timeout);
	__raw_writeb(1, user_dog);

	return 0;
}