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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyLauncherWakeup () ; 
 int /*<<< orphan*/  logicalrep_worker_detach () ; 
 int /*<<< orphan*/  walrcv_disconnect (scalar_t__) ; 
 scalar_t__ wrconn ; 

__attribute__((used)) static void
logicalrep_worker_onexit(int code, Datum arg)
{
	/* Disconnect gracefully from the remote side. */
	if (wrconn)
		walrcv_disconnect(wrconn);

	logicalrep_worker_detach();

	ApplyLauncherWakeup();
}