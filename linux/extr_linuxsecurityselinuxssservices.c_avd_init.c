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
struct av_decision {int auditdeny; scalar_t__ flags; int /*<<< orphan*/  seqno; scalar_t__ auditallow; scalar_t__ allowed; } ;
struct TYPE_2__ {int /*<<< orphan*/  latest_granting; } ;

/* Variables and functions */

__attribute__((used)) static void avd_init(struct selinux_state *state, struct av_decision *avd)
{
	avd->allowed = 0;
	avd->auditallow = 0;
	avd->auditdeny = 0xffffffff;
	avd->seqno = state->ss->latest_granting;
	avd->flags = 0;
}