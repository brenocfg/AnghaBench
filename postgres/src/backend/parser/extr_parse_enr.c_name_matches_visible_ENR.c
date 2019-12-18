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
struct TYPE_3__ {int /*<<< orphan*/  p_queryEnv; } ;
typedef  TYPE_1__ ParseState ;

/* Variables and functions */
 int /*<<< orphan*/ * get_visible_ENR_metadata (int /*<<< orphan*/ ,char const*) ; 

bool
name_matches_visible_ENR(ParseState *pstate, const char *refname)
{
	return (get_visible_ENR_metadata(pstate->p_queryEnv, refname) != NULL);
}