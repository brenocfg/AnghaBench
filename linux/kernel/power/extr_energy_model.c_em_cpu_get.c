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
struct em_perf_domain {int dummy; } ;

/* Variables and functions */
 struct em_perf_domain* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_data ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,int) ; 

struct em_perf_domain *em_cpu_get(int cpu)
{
	return READ_ONCE(per_cpu(em_data, cpu));
}