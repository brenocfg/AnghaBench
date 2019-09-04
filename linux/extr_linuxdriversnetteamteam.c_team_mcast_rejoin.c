#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dw; int /*<<< orphan*/  count_pending; int /*<<< orphan*/  count; } ;
struct team {TYPE_1__ mcast_rejoin; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void team_mcast_rejoin(struct team *team)
{
	if (!team->mcast_rejoin.count || !netif_running(team->dev))
		return;
	atomic_add(team->mcast_rejoin.count, &team->mcast_rejoin.count_pending);
	schedule_delayed_work(&team->mcast_rejoin.dw, 0);
}