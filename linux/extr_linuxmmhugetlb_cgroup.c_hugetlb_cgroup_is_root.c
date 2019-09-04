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
struct hugetlb_cgroup {int dummy; } ;

/* Variables and functions */
 struct hugetlb_cgroup* root_h_cgroup ; 

__attribute__((used)) static inline bool hugetlb_cgroup_is_root(struct hugetlb_cgroup *h_cg)
{
	return (h_cg == root_h_cgroup);
}