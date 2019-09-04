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
struct rpc_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gss_destroy_nullcred (struct rpc_cred*) ; 
 scalar_t__ gss_destroying_context (struct rpc_cred*) ; 

__attribute__((used)) static void
gss_destroy_cred(struct rpc_cred *cred)
{

	if (gss_destroying_context(cred))
		return;
	gss_destroy_nullcred(cred);
}