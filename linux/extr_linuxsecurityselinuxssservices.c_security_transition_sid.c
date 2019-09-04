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
struct qstr {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVTAB_TRANSITION ; 
 int security_compute_sid (struct selinux_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int security_transition_sid(struct selinux_state *state,
			    u32 ssid, u32 tsid, u16 tclass,
			    const struct qstr *qstr, u32 *out_sid)
{
	return security_compute_sid(state, ssid, tsid, tclass,
				    AVTAB_TRANSITION,
				    qstr ? qstr->name : NULL, out_sid, true);
}