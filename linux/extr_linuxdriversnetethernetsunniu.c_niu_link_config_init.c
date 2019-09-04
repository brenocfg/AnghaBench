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
struct niu_link_config {int advertising; int autoneg; int /*<<< orphan*/  loopback_mode; int /*<<< orphan*/  active_duplex; int /*<<< orphan*/  duplex; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  speed; } ;
struct niu {struct niu_link_config link_config; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_INVALID ; 
 int /*<<< orphan*/  LOOPBACK_DISABLED ; 
 int /*<<< orphan*/  SPEED_INVALID ; 

__attribute__((used)) static void niu_link_config_init(struct niu *np)
{
	struct niu_link_config *lp = &np->link_config;

	lp->advertising = (ADVERTISED_10baseT_Half |
			   ADVERTISED_10baseT_Full |
			   ADVERTISED_100baseT_Half |
			   ADVERTISED_100baseT_Full |
			   ADVERTISED_1000baseT_Half |
			   ADVERTISED_1000baseT_Full |
			   ADVERTISED_10000baseT_Full |
			   ADVERTISED_Autoneg);
	lp->speed = lp->active_speed = SPEED_INVALID;
	lp->duplex = DUPLEX_FULL;
	lp->active_duplex = DUPLEX_INVALID;
	lp->autoneg = 1;
#if 0
	lp->loopback_mode = LOOPBACK_MAC;
	lp->active_speed = SPEED_10000;
	lp->active_duplex = DUPLEX_FULL;
#else
	lp->loopback_mode = LOOPBACK_DISABLED;
#endif
}