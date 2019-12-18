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
struct task_struct {int dummy; } ;
struct hugetlb_cgroup {int dummy; } ;

/* Variables and functions */
 struct hugetlb_cgroup* hugetlb_cgroup_from_css (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugetlb_cgrp_id ; 
 int /*<<< orphan*/  task_css (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
struct hugetlb_cgroup *hugetlb_cgroup_from_task(struct task_struct *task)
{
	return hugetlb_cgroup_from_css(task_css(task, hugetlb_cgrp_id));
}