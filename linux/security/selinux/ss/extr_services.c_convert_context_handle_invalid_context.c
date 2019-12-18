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
typedef  int /*<<< orphan*/  u32 ;
struct selinux_state {TYPE_1__* ss; } ;
struct policydb {int dummy; } ;
struct context {int dummy; } ;
struct TYPE_2__ {struct policydb policydb; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  context_struct_to_string (struct policydb*,struct context*,char**,int /*<<< orphan*/ *) ; 
 scalar_t__ enforcing_enabled (struct selinux_state*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 

__attribute__((used)) static inline int convert_context_handle_invalid_context(
	struct selinux_state *state,
	struct context *context)
{
	struct policydb *policydb = &state->ss->policydb;
	char *s;
	u32 len;

	if (enforcing_enabled(state))
		return -EINVAL;

	if (!context_struct_to_string(policydb, context, &s, &len)) {
		pr_warn("SELinux:  Context %s would be invalid if enforcing\n",
			s);
		kfree(s);
	}
	return 0;
}