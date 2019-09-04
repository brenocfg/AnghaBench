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
struct offset_v2 {int /*<<< orphan*/  v; } ;
typedef  unsigned long long loff_t ;

/* Variables and functions */
 unsigned long long le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline loff_t offset_v2_k_offset(const struct offset_v2 *v2)
{
	return le64_to_cpu(v2->v) & (~0ULL >> 4);
}