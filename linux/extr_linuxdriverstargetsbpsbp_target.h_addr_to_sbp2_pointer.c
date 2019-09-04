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
typedef  int u64 ;
struct sbp2_pointer {void* low; void* high; } ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static inline void addr_to_sbp2_pointer(u64 addr, struct sbp2_pointer *ptr)
{
	ptr->high = cpu_to_be32(addr >> 32);
	ptr->low = cpu_to_be32(addr);
}