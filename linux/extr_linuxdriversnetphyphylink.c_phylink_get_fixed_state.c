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
struct phylink_link_state {int link; } ;
struct phylink {scalar_t__ link_gpio; int /*<<< orphan*/  netdev; int /*<<< orphan*/  (* get_fixed_state ) (int /*<<< orphan*/ ,struct phylink_link_state*) ;struct phylink_link_state link_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_get_value_cansleep (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct phylink_link_state*) ; 

__attribute__((used)) static void phylink_get_fixed_state(struct phylink *pl, struct phylink_link_state *state)
{
	*state = pl->link_config;
	if (pl->get_fixed_state)
		pl->get_fixed_state(pl->netdev, state);
	else if (pl->link_gpio)
		state->link = !!gpiod_get_value_cansleep(pl->link_gpio);
}