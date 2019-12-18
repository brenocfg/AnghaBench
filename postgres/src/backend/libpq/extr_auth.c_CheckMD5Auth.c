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
struct TYPE_5__ {int /*<<< orphan*/  user_name; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_REQ_MD5 ; 
 scalar_t__ Db_user_namespace ; 
 int /*<<< orphan*/  ERRCODE_INVALID_AUTHORIZATION_SPECIFICATION ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  LOG ; 
 int STATUS_EOF ; 
 int STATUS_ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int md5_crypt_verify (int /*<<< orphan*/ ,char*,char*,char*,int,char**) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_strong_random (char*,int) ; 
 char* recv_password_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  sendAuthRequest (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
CheckMD5Auth(Port *port, char *shadow_pass, char **logdetail)
{
	char		md5Salt[4];		/* Password salt */
	char	   *passwd;
	int			result;

	if (Db_user_namespace)
		ereport(FATAL,
				(errcode(ERRCODE_INVALID_AUTHORIZATION_SPECIFICATION),
				 errmsg("MD5 authentication is not supported when \"db_user_namespace\" is enabled")));

	/* include the salt to use for computing the response */
	if (!pg_strong_random(md5Salt, 4))
	{
		ereport(LOG,
				(errmsg("could not generate random MD5 salt")));
		return STATUS_ERROR;
	}

	sendAuthRequest(port, AUTH_REQ_MD5, md5Salt, 4);

	passwd = recv_password_packet(port);
	if (passwd == NULL)
		return STATUS_EOF;		/* client wouldn't send password */

	if (shadow_pass)
		result = md5_crypt_verify(port->user_name, shadow_pass, passwd,
								  md5Salt, 4, logdetail);
	else
		result = STATUS_ERROR;

	pfree(passwd);

	return result;
}