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

void
BootStrapCommitTs(void)
{
	/*
	 * Nothing to do here at present, unlike most other SLRU modules; segments
	 * are created when the server is started with this module enabled. See
	 * ActivateCommitTs.
	 */
}