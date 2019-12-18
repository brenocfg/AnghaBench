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
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int SMP_CACHE_BYTES ; 
 size_t copy_from_iter (void*,size_t,struct iov_iter*) ; 
 size_t copy_from_iter_nocache (void*,size_t,struct iov_iter*) ; 
 size_t min (size_t,size_t) ; 
 size_t round_down (size_t,int) ; 

__attribute__((used)) static int tls_device_copy_data(void *addr, size_t bytes, struct iov_iter *i)
{
	size_t pre_copy, nocache;

	pre_copy = ~((unsigned long)addr - 1) & (SMP_CACHE_BYTES - 1);
	if (pre_copy) {
		pre_copy = min(pre_copy, bytes);
		if (copy_from_iter(addr, pre_copy, i) != pre_copy)
			return -EFAULT;
		bytes -= pre_copy;
		addr += pre_copy;
	}

	nocache = round_down(bytes, SMP_CACHE_BYTES);
	if (copy_from_iter_nocache(addr, nocache, i) != nocache)
		return -EFAULT;
	bytes -= nocache;
	addr += nocache;

	if (bytes && copy_from_iter(addr, bytes, i) != bytes)
		return -EFAULT;

	return 0;
}