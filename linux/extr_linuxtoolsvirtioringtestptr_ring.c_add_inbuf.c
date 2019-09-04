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

/* Variables and functions */
 int __ptr_ring_produce (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  array ; 
 int /*<<< orphan*/  headcnt ; 

int add_inbuf(unsigned len, void *buf, void *datap)
{
	int ret;

	ret = __ptr_ring_produce(&array, buf);
	if (ret >= 0) {
		ret = 0;
		headcnt++;
	}

	return ret;
}