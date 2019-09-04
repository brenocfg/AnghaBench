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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 unsigned long long NSEC_PER_SEC ; 
 int S27_TO_NS_SHIFT ; 
 int /*<<< orphan*/  ktime_set (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline ktime_t efx_ptp_s27_to_ktime(u32 nic_major, u32 nic_minor)
{
	u32 ns = (u32)(((u64)nic_minor * NSEC_PER_SEC +
			(1ULL << (S27_TO_NS_SHIFT - 1))) >> S27_TO_NS_SHIFT);
	return ktime_set(nic_major, ns);
}