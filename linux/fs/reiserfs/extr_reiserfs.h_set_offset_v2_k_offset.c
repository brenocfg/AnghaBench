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
struct offset_v2 {int v; } ;
typedef  unsigned long long loff_t ;

/* Variables and functions */
 int cpu_to_le64 (unsigned long long) ; 

__attribute__((used)) static inline void set_offset_v2_k_offset(struct offset_v2 *v2, loff_t offset)
{
	offset &= (~0ULL >> 4);
	v2->v = (v2->v & cpu_to_le64(15ULL << 60)) | cpu_to_le64(offset);
}