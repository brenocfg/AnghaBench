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
struct cpuset {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpumasks (struct cpuset*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cpuset*) ; 

__attribute__((used)) static inline void free_cpuset(struct cpuset *cs)
{
	free_cpumasks(cs, NULL);
	kfree(cs);
}