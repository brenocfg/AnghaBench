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
struct RangeParser {unsigned long long line_number; unsigned long long char_number; } ;

/* Variables and functions */

__attribute__((used)) static void
rangeparse_err(struct RangeParser *p, unsigned long long *line_number, unsigned long long *charindex)
{
    *line_number = p->line_number;
    *charindex = p->char_number;
}