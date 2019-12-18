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
 int /*<<< orphan*/ * comboCids ; 
 int /*<<< orphan*/ * comboHash ; 
 scalar_t__ sizeComboCids ; 
 scalar_t__ usedComboCids ; 

void
AtEOXact_ComboCid(void)
{
	/*
	 * Don't bother to pfree. These are allocated in TopTransactionContext, so
	 * they're going to go away at the end of transaction anyway.
	 */
	comboHash = NULL;

	comboCids = NULL;
	usedComboCids = 0;
	sizeComboCids = 0;
}