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
typedef  int /*<<< orphan*/  pqsigfunc ;

/* Variables and functions */
 int PG_SIGNAL_COUNT ; 
 int /*<<< orphan*/  SIG_ERR ; 
 int /*<<< orphan*/ * pg_signal_array ; 

pqsigfunc
pqsignal(int signum, pqsigfunc handler)
{
	pqsigfunc	prevfunc;

	if (signum >= PG_SIGNAL_COUNT || signum < 0)
		return SIG_ERR;
	prevfunc = pg_signal_array[signum];
	pg_signal_array[signum] = handler;
	return prevfunc;
}