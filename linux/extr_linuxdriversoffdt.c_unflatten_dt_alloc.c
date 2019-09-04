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
 void* PTR_ALIGN (void*,unsigned long) ; 

__attribute__((used)) static void *unflatten_dt_alloc(void **mem, unsigned long size,
				       unsigned long align)
{
	void *res;

	*mem = PTR_ALIGN(*mem, align);
	res = *mem;
	*mem += size;

	return res;
}