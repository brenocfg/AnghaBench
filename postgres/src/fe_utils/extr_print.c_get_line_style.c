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
typedef  int /*<<< orphan*/  printTextFormat ;
struct TYPE_3__ {int /*<<< orphan*/  const* line_style; } ;
typedef  TYPE_1__ printTableOpt ;

/* Variables and functions */
 int /*<<< orphan*/  const pg_asciiformat ; 

const printTextFormat *
get_line_style(const printTableOpt *opt)
{
	/*
	 * Note: this function mainly exists to preserve the convention that a
	 * printTableOpt struct can be initialized to zeroes to get default
	 * behavior.
	 */
	if (opt->line_style != NULL)
		return opt->line_style;
	else
		return &pg_asciiformat;
}