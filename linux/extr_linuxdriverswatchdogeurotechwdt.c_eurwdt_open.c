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
 int /*<<< orphan*/  WDT_TIMEOUT ; 
 int /*<<< orphan*/  eurwdt_activate_timer () ; 
 int /*<<< orphan*/  eurwdt_is_open ; 
 int /*<<< orphan*/  eurwdt_timeout ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eurwdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(0, &eurwdt_is_open))
		return -EBUSY;
	eurwdt_timeout = WDT_TIMEOUT;	/* initial timeout */
	/* Activate the WDT */
	eurwdt_activate_timer();
	return nonseekable_open(inode, file);
}