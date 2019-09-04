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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ outf ; 
 int /*<<< orphan*/  outp ; 
 int /*<<< orphan*/  output_buffer ; 
 scalar_t__ stderr ; 
 int /*<<< orphan*/ * stdout ; 

void flush_output_stdout(void)
{
	FILE *filep;

	if (outf == stderr)
		filep = stdout;
	else
		filep = outf;

	fputs(output_buffer, filep);
	fflush(filep);

	outp = output_buffer;
}