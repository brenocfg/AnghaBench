#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct rdma_cgroup {TYPE_1__ css; } ;

/* Variables and functions */
 struct rdma_cgroup* css_rdmacg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rdma_cgroup *parent_rdmacg(struct rdma_cgroup *cg)
{
	return css_rdmacg(cg->css.parent);
}