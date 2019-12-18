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
typedef  int __u64 ;

/* Variables and functions */
 int XSK_UNALIGNED_BUF_ADDR_MASK ; 

__attribute__((used)) static inline __u64 xsk_umem__extract_addr(__u64 addr)
{
	return addr & XSK_UNALIGNED_BUF_ADDR_MASK;
}