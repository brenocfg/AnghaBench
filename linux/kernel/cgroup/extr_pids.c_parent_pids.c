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
struct pids_cgroup {TYPE_1__ css; } ;

/* Variables and functions */
 struct pids_cgroup* css_pids (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pids_cgroup *parent_pids(struct pids_cgroup *pids)
{
	return css_pids(pids->css.parent);
}