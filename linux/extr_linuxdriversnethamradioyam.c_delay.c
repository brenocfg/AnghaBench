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

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int jiffies ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static void delay(int ms)
{
	unsigned long timeout = jiffies + ((ms * HZ) / 1000);
	while (time_before(jiffies, timeout))
		cpu_relax();
}