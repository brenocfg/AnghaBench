#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tsm_state; } ;
typedef  int /*<<< orphan*/  SystemRowsSamplerData ;
typedef  TYPE_1__ SampleScanState ;

/* Variables and functions */
 int /*<<< orphan*/  palloc0 (int) ; 

__attribute__((used)) static void
system_rows_initsamplescan(SampleScanState *node, int eflags)
{
	node->tsm_state = palloc0(sizeof(SystemRowsSamplerData));
	/* Note the above leaves tsm_state->step equal to zero */
}