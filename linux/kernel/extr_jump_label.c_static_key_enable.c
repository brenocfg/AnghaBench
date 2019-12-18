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
struct static_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpus_read_lock () ; 
 int /*<<< orphan*/  cpus_read_unlock () ; 
 int /*<<< orphan*/  static_key_enable_cpuslocked (struct static_key*) ; 

void static_key_enable(struct static_key *key)
{
	cpus_read_lock();
	static_key_enable_cpuslocked(key);
	cpus_read_unlock();
}