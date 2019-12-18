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
 int /*<<< orphan*/ * host_machine ; 
 int /*<<< orphan*/  machine__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__exit () ; 

void exit_probe_symbol_maps(void)
{
	machine__delete(host_machine);
	host_machine = NULL;
	symbol__exit();
}