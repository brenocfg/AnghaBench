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
struct phylink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  PHYLINK_DISABLE_LINK ; 
 int /*<<< orphan*/  phylink_run_resolve_and_disable (struct phylink*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phylink_sfp_link_down(void *upstream)
{
	struct phylink *pl = upstream;

	ASSERT_RTNL();

	phylink_run_resolve_and_disable(pl, PHYLINK_DISABLE_LINK);
}