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
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  sa1100wdt_users ; 

__attribute__((used)) static int sa1100dog_release(struct inode *inode, struct file *file)
{
	pr_crit("Device closed - timer will not stop\n");
	clear_bit(1, &sa1100wdt_users);
	return 0;
}