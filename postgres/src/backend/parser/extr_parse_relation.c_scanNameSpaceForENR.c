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
typedef  int /*<<< orphan*/  ParseState ;

/* Variables and functions */
 int name_matches_visible_ENR (int /*<<< orphan*/ *,char const*) ; 

bool
scanNameSpaceForENR(ParseState *pstate, const char *refname)
{
	return name_matches_visible_ENR(pstate, refname);
}