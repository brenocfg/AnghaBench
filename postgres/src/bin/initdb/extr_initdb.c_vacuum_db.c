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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PG_CMD_PUTS (char*) ; 

__attribute__((used)) static void
vacuum_db(FILE *cmdfd)
{
	/* Run analyze before VACUUM so the statistics are frozen. */
	PG_CMD_PUTS("ANALYZE;\n\nVACUUM FREEZE;\n\n");
}