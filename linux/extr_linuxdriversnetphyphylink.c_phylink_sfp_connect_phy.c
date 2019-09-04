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
struct TYPE_2__ {int /*<<< orphan*/  interface; } ;
struct phylink {TYPE_1__ link_config; } ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int __phylink_connect_phy (void*,struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phylink_sfp_connect_phy(void *upstream, struct phy_device *phy)
{
	struct phylink *pl = upstream;

	return __phylink_connect_phy(upstream, phy, pl->link_config.interface);
}