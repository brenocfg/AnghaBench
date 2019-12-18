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
struct rdma_cgroup {int dummy; } ;

/* Variables and functions */
 struct rdma_cgroup* css_rdmacg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  rdma_cgrp_id ; 
 int /*<<< orphan*/  task_get_css (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct rdma_cgroup *get_current_rdmacg(void)
{
	return css_rdmacg(task_get_css(current, rdma_cgrp_id));
}