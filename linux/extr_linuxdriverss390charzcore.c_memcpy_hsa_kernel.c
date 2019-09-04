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
 int EIO ; 
 int ENODATA ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  hsa_available ; 
 scalar_t__ hsa_buf ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,unsigned long) ; 
 unsigned long min (unsigned long,size_t) ; 
 scalar_t__ sclp_sdias_copy (scalar_t__,unsigned long,int) ; 

int memcpy_hsa_kernel(void *dest, unsigned long src, size_t count)
{
	unsigned long offset, bytes;

	if (!hsa_available)
		return -ENODATA;

	while (count) {
		if (sclp_sdias_copy(hsa_buf, src / PAGE_SIZE + 2, 1)) {
			TRACE("sclp_sdias_copy() failed\n");
			return -EIO;
		}
		offset = src % PAGE_SIZE;
		bytes = min(PAGE_SIZE - offset, count);
		memcpy(dest, hsa_buf + offset, bytes);
		src += bytes;
		dest += bytes;
		count -= bytes;
	}
	return 0;
}