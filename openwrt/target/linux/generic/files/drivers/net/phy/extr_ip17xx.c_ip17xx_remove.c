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
struct phy_device {struct ip17xx_state* priv; } ;
struct ip17xx_state {int /*<<< orphan*/  dev; scalar_t__ registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ip17xx_state*) ; 
 int /*<<< orphan*/  unregister_switch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip17xx_remove(struct phy_device *pdev)
{
	struct ip17xx_state *state = pdev->priv;

	if (state->registered)
		unregister_switch(&state->dev);
	kfree(state);
}