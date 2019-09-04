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
typedef  size_t uint16 ;
typedef  int /*<<< orphan*/ * RD_HCURSOR ;

/* Variables and functions */
 size_t NUM_ELEMENTS (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  error (char*,size_t) ; 
 int /*<<< orphan*/ ** g_cursorcache ; 
 int /*<<< orphan*/  ui_destroy_cursor (int /*<<< orphan*/ *) ; 

void
cache_put_cursor(uint16 cache_idx, RD_HCURSOR cursor)
{
	RD_HCURSOR old;

	if (cache_idx < NUM_ELEMENTS(g_cursorcache))
	{
		old = g_cursorcache[cache_idx];
		if (old != NULL)
			ui_destroy_cursor(old);

		g_cursorcache[cache_idx] = cursor;
	}
	else
	{
		error("put cursor %d\n", cache_idx);
	}
}