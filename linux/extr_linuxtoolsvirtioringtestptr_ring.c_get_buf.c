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
 scalar_t__ __ptr_ring_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array ; 
 scalar_t__ headcnt ; 
 scalar_t__ tailcnt ; 

void *get_buf(unsigned *lenp, void **bufp)
{
	void *datap;

	if (tailcnt == headcnt || __ptr_ring_full(&array))
		datap = NULL;
	else {
		datap = "Buffer\n";
		++tailcnt;
	}

	return datap;
}