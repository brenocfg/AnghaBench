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
 int /*<<< orphan*/  AtCCI_RelationMap () ; 
 int /*<<< orphan*/  CommandEndInvalidationMessages () ; 

__attribute__((used)) static void
AtCCI_LocalCache(void)
{
	/*
	 * Make any pending relation map changes visible.  We must do this before
	 * processing local sinval messages, so that the map changes will get
	 * reflected into the relcache when relcache invals are processed.
	 */
	AtCCI_RelationMap();

	/*
	 * Make catalog changes visible to me for the next command.
	 */
	CommandEndInvalidationMessages();
}