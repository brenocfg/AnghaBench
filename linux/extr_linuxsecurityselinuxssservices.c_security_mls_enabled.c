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
struct selinux_state {TYPE_1__* ss; } ;
struct policydb {int mls_enabled; } ;
struct TYPE_2__ {struct policydb policydb; } ;

/* Variables and functions */

int security_mls_enabled(struct selinux_state *state)
{
	struct policydb *p = &state->ss->policydb;

	return p->mls_enabled;
}