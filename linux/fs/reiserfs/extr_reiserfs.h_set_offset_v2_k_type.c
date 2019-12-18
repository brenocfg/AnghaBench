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
typedef  int __u64 ;

/* Variables and functions */
 int cpu_to_le64 (int) ; 

__attribute__((used)) static inline void set_offset_v2_k_type(struct offset_v2 *v2, int type)
{
	v2->v =
	    (v2->v & cpu_to_le64(~0ULL >> 4)) | cpu_to_le64((__u64) type << 60);
}