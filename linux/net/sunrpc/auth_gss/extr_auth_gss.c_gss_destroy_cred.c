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
struct rpc_cred {int /*<<< orphan*/  cr_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPCAUTH_CRED_UPTODATE ; 
 int /*<<< orphan*/  gss_destroy_nullcred (struct rpc_cred*) ; 
 int /*<<< orphan*/  gss_send_destroy_context (struct rpc_cred*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gss_destroy_cred(struct rpc_cred *cred)
{

	if (test_and_clear_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags) != 0)
		gss_send_destroy_context(cred);
	gss_destroy_nullcred(cred);
}