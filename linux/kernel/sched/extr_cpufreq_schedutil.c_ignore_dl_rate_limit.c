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
struct sugov_policy {int limits_changed; } ;
struct sugov_cpu {scalar_t__ bw_dl; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 scalar_t__ cpu_bw_dl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_rq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ignore_dl_rate_limit(struct sugov_cpu *sg_cpu, struct sugov_policy *sg_policy)
{
	if (cpu_bw_dl(cpu_rq(sg_cpu->cpu)) > sg_cpu->bw_dl)
		sg_policy->limits_changed = true;
}