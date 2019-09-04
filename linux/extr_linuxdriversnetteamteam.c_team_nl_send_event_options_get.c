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
struct team {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  team_nl_send_multicast ; 
 int team_nl_send_options_get (struct team*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct list_head*) ; 

__attribute__((used)) static int team_nl_send_event_options_get(struct team *team,
					  struct list_head *sel_opt_inst_list)
{
	return team_nl_send_options_get(team, 0, 0, 0, team_nl_send_multicast,
					sel_opt_inst_list);
}