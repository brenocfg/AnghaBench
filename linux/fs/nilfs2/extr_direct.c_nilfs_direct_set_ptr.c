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
struct nilfs_bmap {int dummy; } ;
typedef  int __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/ * nilfs_direct_dptrs (struct nilfs_bmap*) ; 

__attribute__((used)) static inline void nilfs_direct_set_ptr(struct nilfs_bmap *direct,
					__u64 key, __u64 ptr)
{
	*(nilfs_direct_dptrs(direct) + key) = cpu_to_le64(ptr);
}