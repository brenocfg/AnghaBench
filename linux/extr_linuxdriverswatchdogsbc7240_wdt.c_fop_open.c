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
 int /*<<< orphan*/  SBC7240_OPEN_STATUS_BIT ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_enable () ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static int fop_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(SBC7240_OPEN_STATUS_BIT, &wdt_status))
		return -EBUSY;

	wdt_enable();

	return nonseekable_open(inode, file);
}