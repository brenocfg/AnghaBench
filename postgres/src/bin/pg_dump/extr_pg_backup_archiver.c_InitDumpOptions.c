#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int include_everything; int /*<<< orphan*/  dumpSections; } ;
typedef  TYPE_1__ DumpOptions ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_UNSECTIONED ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
InitDumpOptions(DumpOptions *opts)
{
	memset(opts, 0, sizeof(DumpOptions));
	/* set any fields that shouldn't default to zeroes */
	opts->include_everything = true;
	opts->dumpSections = DUMP_UNSECTIONED;
}