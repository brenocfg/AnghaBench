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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct selinux_state {int dummy; } ;

/* Variables and functions */
 int security_compute_validatetrans (struct selinux_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int security_validate_transition(struct selinux_state *state,
				 u32 oldsid, u32 newsid, u32 tasksid,
				 u16 orig_tclass)
{
	return security_compute_validatetrans(state, oldsid, newsid, tasksid,
					      orig_tclass, false);
}