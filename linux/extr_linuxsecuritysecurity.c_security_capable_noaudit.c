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
struct user_namespace {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECURITY_CAP_NOAUDIT ; 
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*,struct user_namespace*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable ; 

int security_capable_noaudit(const struct cred *cred, struct user_namespace *ns,
			     int cap)
{
	return call_int_hook(capable, 0, cred, ns, cap, SECURITY_CAP_NOAUDIT);
}