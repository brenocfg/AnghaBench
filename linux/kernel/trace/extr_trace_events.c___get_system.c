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
struct event_subsystem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ system_refcount (struct event_subsystem*) ; 
 int /*<<< orphan*/  system_refcount_inc (struct event_subsystem*) ; 

__attribute__((used)) static void __get_system(struct event_subsystem *system)
{
	WARN_ON_ONCE(system_refcount(system) == 0);
	system_refcount_inc(system);
}