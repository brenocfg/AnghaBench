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
struct switch_dev {int dummy; } ;
struct ip17xx_state {TYPE_1__* ports; } ;
struct TYPE_2__ {int pvid; } ;

/* Variables and functions */
 struct ip17xx_state* get_state (struct switch_dev*) ; 

__attribute__((used)) static int ip17xx_get_pvid(struct switch_dev *dev, int port, int *val)
{
	struct ip17xx_state *state = get_state(dev);

	*val = state->ports[port].pvid;
	return 0;
}