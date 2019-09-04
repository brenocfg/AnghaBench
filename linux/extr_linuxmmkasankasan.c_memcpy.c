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
 int /*<<< orphan*/  _RET_IP_ ; 
 void* __memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  check_memory_region (unsigned long,size_t,int,int /*<<< orphan*/ ) ; 

void *memcpy(void *dest, const void *src, size_t len)
{
	check_memory_region((unsigned long)src, len, false, _RET_IP_);
	check_memory_region((unsigned long)dest, len, true, _RET_IP_);

	return __memcpy(dest, src, len);
}