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
struct TYPE_2__ {int* cap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 TYPE_1__* handles ; 

__attribute__((used)) static int sony_find_snc_handle(int handle)
{
	int i;

	/* not initialized yet, return early */
	if (!handles || !handle)
		return -EINVAL;

	for (i = 0; i < 0x10; i++) {
		if (handles->cap[i] == handle) {
			dprintk("found handle 0x%.4x (offset: 0x%.2x)\n",
					handle, i);
			return i;
		}
	}
	dprintk("handle 0x%.4x not found\n", handle);
	return -EINVAL;
}