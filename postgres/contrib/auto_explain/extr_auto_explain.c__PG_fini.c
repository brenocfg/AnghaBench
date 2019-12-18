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
 int /*<<< orphan*/  ExecutorEnd_hook ; 
 int /*<<< orphan*/  ExecutorFinish_hook ; 
 int /*<<< orphan*/  ExecutorRun_hook ; 
 int /*<<< orphan*/  ExecutorStart_hook ; 
 int /*<<< orphan*/  prev_ExecutorEnd ; 
 int /*<<< orphan*/  prev_ExecutorFinish ; 
 int /*<<< orphan*/  prev_ExecutorRun ; 
 int /*<<< orphan*/  prev_ExecutorStart ; 

void
_PG_fini(void)
{
	/* Uninstall hooks. */
	ExecutorStart_hook = prev_ExecutorStart;
	ExecutorRun_hook = prev_ExecutorRun;
	ExecutorFinish_hook = prev_ExecutorFinish;
	ExecutorEnd_hook = prev_ExecutorEnd;
}