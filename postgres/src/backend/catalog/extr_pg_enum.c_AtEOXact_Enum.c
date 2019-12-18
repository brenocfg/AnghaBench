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
 int /*<<< orphan*/ * enum_blacklist ; 

void
AtEOXact_Enum(void)
{
	/*
	 * Reset the blacklist table, as all our enum values are now committed.
	 * The memory will go away automatically when TopTransactionContext is
	 * freed; it's sufficient to clear our pointer.
	 */
	enum_blacklist = NULL;
}