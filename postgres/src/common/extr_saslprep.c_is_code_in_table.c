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
typedef  scalar_t__ const pg_wchar ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ bsearch (scalar_t__ const*,scalar_t__ const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codepoint_range_cmp ; 

__attribute__((used)) static bool
is_code_in_table(pg_wchar code, const pg_wchar *map, int mapsize)
{
	Assert(mapsize % 2 == 0);

	if (code < map[0] || code > map[mapsize - 1])
		return false;

	if (bsearch(&code, map, mapsize / 2, sizeof(pg_wchar) * 2,
				codepoint_range_cmp))
		return true;
	else
		return false;
}