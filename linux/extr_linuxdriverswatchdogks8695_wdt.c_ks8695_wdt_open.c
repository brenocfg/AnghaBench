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
 int /*<<< orphan*/  ks8695_wdt_start () ; 
 int /*<<< orphan*/  ks8695wdt_busy ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ks8695_wdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(0, &ks8695wdt_busy))
		return -EBUSY;

	ks8695_wdt_start();
	return nonseekable_open(inode, file);
}