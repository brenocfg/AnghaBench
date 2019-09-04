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
 int memcmp (void*,void*,size_t) ; 

__attribute__((used)) static bool intel_pt_compare_buffers(void *buf1, size_t compare_size,
				     void *buf2, size_t offs2, size_t buf2_size)
{
	size_t end2 = offs2 + compare_size, part_size;

	if (end2 <= buf2_size)
		return memcmp(buf1, buf2 + offs2, compare_size);

	part_size = end2 - buf2_size;
	if (memcmp(buf1, buf2 + offs2, part_size))
		return true;

	compare_size -= part_size;

	return memcmp(buf1 + part_size, buf2, compare_size);
}