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
typedef  int /*<<< orphan*/  SyncRepConfigData ;

/* Variables and functions */
 int /*<<< orphan*/ * SyncRepConfig ; 

void
assign_synchronous_standby_names(const char *newval, void *extra)
{
	SyncRepConfig = (SyncRepConfigData *) extra;
}