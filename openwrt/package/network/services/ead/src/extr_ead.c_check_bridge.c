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
 int /*<<< orphan*/  br_foreach_port (char const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  check_bridge_port ; 

__attribute__((used)) static int
check_bridge(const char *name, void *arg)
{
	br_foreach_port(name, check_bridge_port, arg);
	return 0;
}