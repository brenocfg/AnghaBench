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
struct selinux_state {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  SECSID_NULL ; 
 int security_context_to_sid_core (struct selinux_state*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int security_context_to_sid(struct selinux_state *state,
			    const char *scontext, u32 scontext_len, u32 *sid,
			    gfp_t gfp)
{
	return security_context_to_sid_core(state, scontext, scontext_len,
					    sid, SECSID_NULL, gfp, 0);
}