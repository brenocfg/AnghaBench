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
struct TYPE_3__ {int /*<<< orphan*/  dumpSections; int /*<<< orphan*/  promptPassword; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ RestoreOptions ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_UNSECTIONED ; 
 int /*<<< orphan*/  TRI_DEFAULT ; 
 int /*<<< orphan*/  archUnknown ; 
 scalar_t__ pg_malloc0 (int) ; 

RestoreOptions *
NewRestoreOptions(void)
{
	RestoreOptions *opts;

	opts = (RestoreOptions *) pg_malloc0(sizeof(RestoreOptions));

	/* set any fields that shouldn't default to zeroes */
	opts->format = archUnknown;
	opts->promptPassword = TRI_DEFAULT;
	opts->dumpSections = DUMP_UNSECTIONED;

	return opts;
}