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
struct char_device_struct {int dummy; } ;
typedef  unsigned int dev_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct char_device_struct*) ; 
 scalar_t__ MAJOR (unsigned int) ; 
 int /*<<< orphan*/  MINOR (unsigned int) ; 
 unsigned int MKDEV (scalar_t__,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct char_device_struct*) ; 
 struct char_device_struct* __register_chrdev_region (scalar_t__,int /*<<< orphan*/ ,unsigned int,char const*) ; 
 int /*<<< orphan*/  __unregister_chrdev_region (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

int register_chrdev_region(dev_t from, unsigned count, const char *name)
{
	struct char_device_struct *cd;
	dev_t to = from + count;
	dev_t n, next;

	for (n = from; n < to; n = next) {
		next = MKDEV(MAJOR(n)+1, 0);
		if (next > to)
			next = to;
		cd = __register_chrdev_region(MAJOR(n), MINOR(n),
			       next - n, name);
		if (IS_ERR(cd))
			goto fail;
	}
	return 0;
fail:
	to = n;
	for (n = from; n < to; n = next) {
		next = MKDEV(MAJOR(n)+1, 0);
		kfree(__unregister_chrdev_region(MAJOR(n), MINOR(n), next - n));
	}
	return PTR_ERR(cd);
}