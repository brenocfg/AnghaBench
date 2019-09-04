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
struct team_option {int dummy; } ;
struct team {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __team_options_change_check (struct team*) ; 
 int /*<<< orphan*/  __team_options_mark_removed (struct team*,struct team_option const*,size_t) ; 
 int /*<<< orphan*/  __team_options_unregister (struct team*,struct team_option const*,size_t) ; 

void team_options_unregister(struct team *team,
			     const struct team_option *option,
			     size_t option_count)
{
	__team_options_mark_removed(team, option, option_count);
	__team_options_change_check(team);
	__team_options_unregister(team, option, option_count);
}