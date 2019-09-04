#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ receive; scalar_t__ transmit; } ;
struct team {TYPE_3__* mode; TYPE_1__ ops; int /*<<< orphan*/  en_port_count; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {scalar_t__ receive; scalar_t__ transmit; } ;

/* Variables and functions */
 scalar_t__ team_dummy_receive ; 
 scalar_t__ team_dummy_transmit ; 
 int /*<<< orphan*/  team_is_mode_set (struct team*) ; 

__attribute__((used)) static void team_adjust_ops(struct team *team)
{
	/*
	 * To avoid checks in rx/tx skb paths, ensure here that non-null and
	 * correct ops are always set.
	 */

	if (!team->en_port_count || !team_is_mode_set(team) ||
	    !team->mode->ops->transmit)
		team->ops.transmit = team_dummy_transmit;
	else
		team->ops.transmit = team->mode->ops->transmit;

	if (!team->en_port_count || !team_is_mode_set(team) ||
	    !team->mode->ops->receive)
		team->ops.receive = team_dummy_receive;
	else
		team->ops.receive = team->mode->ops->receive;
}