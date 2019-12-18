#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* hba; int /*<<< orphan*/  user_name; } ;
struct TYPE_6__ {scalar_t__ auth_method; } ;
typedef  TYPE_2__ Port ;
typedef  scalar_t__ PasswordType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int CheckMD5Auth (TYPE_2__*,char*,char**) ; 
 int CheckSCRAMAuth (TYPE_2__*,char*,char**) ; 
 scalar_t__ PASSWORD_TYPE_MD5 ; 
 scalar_t__ Password_encryption ; 
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 scalar_t__ get_password_type (char*) ; 
 char* get_role_password (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 scalar_t__ uaMD5 ; 
 scalar_t__ uaSCRAM ; 

__attribute__((used)) static int
CheckPWChallengeAuth(Port *port, char **logdetail)
{
	int			auth_result;
	char	   *shadow_pass;
	PasswordType pwtype;

	Assert(port->hba->auth_method == uaSCRAM ||
		   port->hba->auth_method == uaMD5);

	/* First look up the user's password. */
	shadow_pass = get_role_password(port->user_name, logdetail);

	/*
	 * If the user does not exist, or has no password or it's expired, we
	 * still go through the motions of authentication, to avoid revealing to
	 * the client that the user didn't exist.  If 'md5' is allowed, we choose
	 * whether to use 'md5' or 'scram-sha-256' authentication based on current
	 * password_encryption setting.  The idea is that most genuine users
	 * probably have a password of that type, and if we pretend that this user
	 * had a password of that type, too, it "blends in" best.
	 */
	if (!shadow_pass)
		pwtype = Password_encryption;
	else
		pwtype = get_password_type(shadow_pass);

	/*
	 * If 'md5' authentication is allowed, decide whether to perform 'md5' or
	 * 'scram-sha-256' authentication based on the type of password the user
	 * has.  If it's an MD5 hash, we must do MD5 authentication, and if it's a
	 * SCRAM secret, we must do SCRAM authentication.
	 *
	 * If MD5 authentication is not allowed, always use SCRAM.  If the user
	 * had an MD5 password, CheckSCRAMAuth() will fail.
	 */
	if (port->hba->auth_method == uaMD5 && pwtype == PASSWORD_TYPE_MD5)
		auth_result = CheckMD5Auth(port, shadow_pass, logdetail);
	else
		auth_result = CheckSCRAMAuth(port, shadow_pass, logdetail);

	if (shadow_pass)
		pfree(shadow_pass);

	/*
	 * If get_role_password() returned error, return error, even if the
	 * authentication succeeded.
	 */
	if (!shadow_pass)
	{
		Assert(auth_result != STATUS_OK);
		return STATUS_ERROR;
	}
	return auth_result;
}