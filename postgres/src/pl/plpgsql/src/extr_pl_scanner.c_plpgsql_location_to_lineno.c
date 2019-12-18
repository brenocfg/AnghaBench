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
 char const* cur_line_end ; 
 int cur_line_num ; 
 char const* cur_line_start ; 
 int /*<<< orphan*/  location_lineno_init () ; 
 char* scanorig ; 
 char* strchr (char const*,char) ; 

int
plpgsql_location_to_lineno(int location)
{
	const char *loc;

	if (location < 0 || scanorig == NULL)
		return 0;				/* garbage in, garbage out */
	loc = scanorig + location;

	/* be correct, but not fast, if input location goes backwards */
	if (loc < cur_line_start)
		location_lineno_init();

	while (cur_line_end != NULL && loc > cur_line_end)
	{
		cur_line_start = cur_line_end + 1;
		cur_line_num++;
		cur_line_end = strchr(cur_line_start, '\n');
	}

	return cur_line_num;
}