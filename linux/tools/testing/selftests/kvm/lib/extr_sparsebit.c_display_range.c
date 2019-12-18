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
typedef  int /*<<< orphan*/  sparsebit_idx_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t display_range(FILE *stream, sparsebit_idx_t low,
	sparsebit_idx_t high, bool prepend_comma_space)
{
	char *fmt_str;
	size_t sz;

	/* Determine the printf format string */
	if (low == high)
		fmt_str = prepend_comma_space ? ", 0x%lx" : "0x%lx";
	else
		fmt_str = prepend_comma_space ? ", 0x%lx:0x%lx" : "0x%lx:0x%lx";

	/*
	 * When stream is NULL, just determine the size of what would
	 * have been printed, else print the range.
	 */
	if (!stream)
		sz = snprintf(NULL, 0, fmt_str, low, high);
	else
		sz = fprintf(stream, fmt_str, low, high);

	return sz;
}