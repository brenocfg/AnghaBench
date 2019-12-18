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
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  TopTransactionResourceOwner ; 

__attribute__((used)) static void
AtAbort_ResourceOwner(void)
{
	/*
	 * Make sure we have a valid ResourceOwner, if possible (else it will be
	 * NULL, which is OK)
	 */
	CurrentResourceOwner = TopTransactionResourceOwner;
}