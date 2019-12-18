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

/* Variables and functions */
 int security_sid_to_context_core (struct selinux_state*,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int security_sid_to_context_force(struct selinux_state *state, u32 sid,
				  char **scontext, u32 *scontext_len)
{
	return security_sid_to_context_core(state, sid, scontext,
					    scontext_len, 1, 0);
}