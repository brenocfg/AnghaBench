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
typedef  int /*<<< orphan*/  u8 ;
struct dsa_port {int dummy; } ;

/* Variables and functions */
 int dsa_port_set_state (struct dsa_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dsa_port_set_state_now(struct dsa_port *dp, u8 state)
{
	int err;

	err = dsa_port_set_state(dp, state, NULL);
	if (err)
		pr_err("DSA: failed to set STP state %u (%d)\n", state, err);
}