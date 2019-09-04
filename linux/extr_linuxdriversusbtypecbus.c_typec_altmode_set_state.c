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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct typec_altmode {TYPE_1__ dev; } ;
struct altmode {int /*<<< orphan*/  nh; struct altmode* partner; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int is_typec_port (int /*<<< orphan*/ ) ; 
 struct altmode* to_altmode (struct typec_altmode*) ; 
 int typec_altmode_set_mux (struct altmode*,int) ; 

__attribute__((used)) static int typec_altmode_set_state(struct typec_altmode *adev, int state)
{
	bool is_port = is_typec_port(adev->dev.parent);
	struct altmode *port_altmode;
	int ret;

	port_altmode = is_port ? to_altmode(adev) : to_altmode(adev)->partner;

	ret = typec_altmode_set_mux(port_altmode, state);
	if (ret)
		return ret;

	blocking_notifier_call_chain(&port_altmode->nh, state, NULL);

	return 0;
}