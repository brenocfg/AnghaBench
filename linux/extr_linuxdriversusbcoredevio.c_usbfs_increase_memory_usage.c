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
typedef  int u64 ;

/* Variables and functions */
 int ENOMEM ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 int atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbfs_memory_mb ; 
 int /*<<< orphan*/  usbfs_memory_usage ; 

__attribute__((used)) static int usbfs_increase_memory_usage(u64 amount)
{
	u64 lim;

	lim = READ_ONCE(usbfs_memory_mb);
	lim <<= 20;

	atomic64_add(amount, &usbfs_memory_usage);

	if (lim > 0 && atomic64_read(&usbfs_memory_usage) > lim) {
		atomic64_sub(amount, &usbfs_memory_usage);
		return -ENOMEM;
	}

	return 0;
}