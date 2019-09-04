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
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  kernel_cap_t ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred*,struct cred const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  capset ; 

int security_capset(struct cred *new, const struct cred *old,
		    const kernel_cap_t *effective,
		    const kernel_cap_t *inheritable,
		    const kernel_cap_t *permitted)
{
	return call_int_hook(capset, 0, new, old,
				effective, inheritable, permitted);
}