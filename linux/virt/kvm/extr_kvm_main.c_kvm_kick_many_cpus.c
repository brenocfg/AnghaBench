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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ack_flush ; 
 struct cpumask* cpu_online_mask ; 
 scalar_t__ cpumask_empty (struct cpumask const*) ; 
 int /*<<< orphan*/  smp_call_function_many (struct cpumask const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool kvm_kick_many_cpus(const struct cpumask *cpus, bool wait)
{
	if (unlikely(!cpus))
		cpus = cpu_online_mask;

	if (cpumask_empty(cpus))
		return false;

	smp_call_function_many(cpus, ack_flush, NULL, wait);
	return true;
}