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
 int /*<<< orphan*/  CheckForLocalBufferLeaks () ; 

void
AtProcExit_LocalBuffers(void)
{
	/*
	 * We shouldn't be holding any remaining pins; if we are, and assertions
	 * aren't enabled, we'll fail later in DropRelFileNodeBuffers while trying
	 * to drop the temp rels.
	 */
	CheckForLocalBufferLeaks();
}