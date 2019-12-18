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
 int pg_signal_mask ; 
 int /*<<< orphan*/  pgwin32_dispatch_queued_signals () ; 

int
pqsigsetmask(int mask)
{
	int			prevmask;

	prevmask = pg_signal_mask;
	pg_signal_mask = mask;

	/*
	 * Dispatch any signals queued up right away, in case we have unblocked
	 * one or more signals previously queued
	 */
	pgwin32_dispatch_queued_signals();

	return prevmask;
}