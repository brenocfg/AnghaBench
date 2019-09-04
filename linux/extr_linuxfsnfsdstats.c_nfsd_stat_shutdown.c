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
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  svc_proc_unregister (int /*<<< orphan*/ *,char*) ; 

void
nfsd_stat_shutdown(void)
{
	svc_proc_unregister(&init_net, "nfsd");
}