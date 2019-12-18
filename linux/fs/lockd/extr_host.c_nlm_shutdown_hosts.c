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
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  nlm_shutdown_hosts_net (int /*<<< orphan*/ *) ; 

void
nlm_shutdown_hosts(void)
{
	dprintk("lockd: shutting down host module\n");
	nlm_shutdown_hosts_net(NULL);
}