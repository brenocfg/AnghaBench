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

/* Variables and functions */
 int /*<<< orphan*/  ClientAuthentication_hook ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  RegisterSubXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterXactCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_label_peer ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  fmgr_hook ; 
 scalar_t__ getcon_raw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  needs_fmgr_hook ; 
 int /*<<< orphan*/  next_client_auth_hook ; 
 int /*<<< orphan*/  next_fmgr_hook ; 
 int /*<<< orphan*/  next_needs_fmgr_hook ; 
 int /*<<< orphan*/  sepgsql_client_auth ; 
 int /*<<< orphan*/  sepgsql_fmgr_hook ; 
 int /*<<< orphan*/  sepgsql_needs_fmgr_hook ; 
 int /*<<< orphan*/  sepgsql_subxact_callback ; 
 int /*<<< orphan*/  sepgsql_xact_callback ; 

void
sepgsql_init_client_label(void)
{
	/*
	 * Set up dummy client label.
	 *
	 * XXX - note that PostgreSQL launches background worker process like
	 * autovacuum without authentication steps. So, we initialize sepgsql_mode
	 * with SEPGSQL_MODE_INTERNAL, and client_label with the security context
	 * of server process. Later, it also launches background of user session.
	 * In this case, the process is always hooked on post-authentication, and
	 * we can initialize the sepgsql_mode and client_label correctly.
	 */
	if (getcon_raw(&client_label_peer) < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("SELinux: failed to get server security label: %m")));

	/* Client authentication hook */
	next_client_auth_hook = ClientAuthentication_hook;
	ClientAuthentication_hook = sepgsql_client_auth;

	/* Trusted procedure hooks */
	next_needs_fmgr_hook = needs_fmgr_hook;
	needs_fmgr_hook = sepgsql_needs_fmgr_hook;

	next_fmgr_hook = fmgr_hook;
	fmgr_hook = sepgsql_fmgr_hook;

	/* Transaction/Sub-transaction callbacks */
	RegisterXactCallback(sepgsql_xact_callback, NULL);
	RegisterSubXactCallback(sepgsql_subxact_callback, NULL);
}