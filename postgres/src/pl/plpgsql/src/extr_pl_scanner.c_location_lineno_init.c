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
 int /*<<< orphan*/  cur_line_end ; 
 int cur_line_num ; 
 int /*<<< orphan*/  cur_line_start ; 
 int /*<<< orphan*/  scanorig ; 
 int /*<<< orphan*/  strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void
location_lineno_init(void)
{
	cur_line_start = scanorig;
	cur_line_num = 1;

	cur_line_end = strchr(cur_line_start, '\n');
}