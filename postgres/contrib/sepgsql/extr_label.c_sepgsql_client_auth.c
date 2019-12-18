#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  SEPGSQL_MODE_DEFAULT ; 
 int /*<<< orphan*/  SEPGSQL_MODE_PERMISSIVE ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  client_label_peer ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ getpeercon_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_client_auth_hook (TYPE_1__*,int) ; 
 scalar_t__ sepgsql_get_permissive () ; 
 int /*<<< orphan*/  sepgsql_set_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static void
sepgsql_client_auth(Port *port, int status)
{
	if (next_client_auth_hook)
		(*next_client_auth_hook) (port, status);

	/*
	 * In the case when authentication failed, the supplied socket shall be
	 * closed soon, so we don't need to do anything here.
	 */
	if (status != STATUS_OK)
		return;

	/*
	 * Getting security label of the peer process using API of libselinux.
	 */
	if (getpeercon_raw(port->sock, &client_label_peer) < 0)
		ereport(FATAL,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("SELinux: unable to get peer label: %m")));

	/*
	 * Switch the current performing mode from INTERNAL to either DEFAULT or
	 * PERMISSIVE.
	 */
	if (sepgsql_get_permissive())
		sepgsql_set_mode(SEPGSQL_MODE_PERMISSIVE);
	else
		sepgsql_set_mode(SEPGSQL_MODE_DEFAULT);
}