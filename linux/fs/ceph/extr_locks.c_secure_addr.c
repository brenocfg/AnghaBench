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
typedef  unsigned long long u64 ;

/* Variables and functions */
 unsigned long long lock_secret ; 

__attribute__((used)) static inline u64 secure_addr(void *addr)
{
	u64 v = lock_secret ^ (u64)(unsigned long)addr;
	/*
	 * Set the most significant bit, so that MDS knows the 'owner'
	 * is sufficient to identify the owner of lock. (old code uses
	 * both 'owner' and 'pid')
	 */
	v |= (1ULL << 63);
	return v;
}