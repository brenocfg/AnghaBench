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
struct target {int /*<<< orphan*/  uses_mmap; scalar_t__ per_thread; scalar_t__ default_per_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  target__has_cpu (struct target*) ; 
 scalar_t__ target__has_per_thread (struct target*) ; 
 scalar_t__ target__has_task (struct target*) ; 

__attribute__((used)) static inline bool target__uses_dummy_map(struct target *target)
{
	bool use_dummy = false;

	if (target->default_per_cpu)
		use_dummy = target->per_thread ? true : false;
	else if (target__has_task(target) ||
	         (!target__has_cpu(target) && !target->uses_mmap))
		use_dummy = true;
	else if (target__has_per_thread(target))
		use_dummy = true;

	return use_dummy;
}