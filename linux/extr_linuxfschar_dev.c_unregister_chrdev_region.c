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
typedef  unsigned int dev_t ;

/* Variables and functions */
 scalar_t__ MAJOR (unsigned int) ; 
 int /*<<< orphan*/  MINOR (unsigned int) ; 
 unsigned int MKDEV (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __unregister_chrdev_region (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void unregister_chrdev_region(dev_t from, unsigned count)
{
	dev_t to = from + count;
	dev_t n, next;

	for (n = from; n < to; n = next) {
		next = MKDEV(MAJOR(n)+1, 0);
		if (next > to)
			next = to;
		kfree(__unregister_chrdev_region(MAJOR(n), MINOR(n), next - n));
	}
}