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
 int /*<<< orphan*/  scanner_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scanorig ; 
 int /*<<< orphan*/ * yyscanner ; 

void
plpgsql_scanner_finish(void)
{
	/* release storage */
	scanner_finish(yyscanner);
	/* avoid leaving any dangling pointers */
	yyscanner = NULL;
	scanorig = NULL;
}