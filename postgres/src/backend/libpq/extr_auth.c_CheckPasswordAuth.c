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
 int /*<<< orphan*/  AUTH_REQ_PASSWORD ; 
 int STATUS_EOF ; 
 int STATUS_ERROR ; 
 char* get_role_password (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int plain_crypt_verify (int /*<<< orphan*/ ,char*,char*,char**) ; 
 char* recv_password_packet (TYPE_1__*) ; 
 int /*<<< orphan*/  sendAuthRequest (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
CheckPasswordAuth(Port *port, char **logdetail)
{
	char	   *passwd;
	int			result;
	char	   *shadow_pass;

	sendAuthRequest(port, AUTH_REQ_PASSWORD, NULL, 0);

	passwd = recv_password_packet(port);
	if (passwd == NULL)
		return STATUS_EOF;		/* client wouldn't send password */

	shadow_pass = get_role_password(port->user_name, logdetail);
	if (shadow_pass)
	{
		result = plain_crypt_verify(port->user_name, shadow_pass, passwd,
									logdetail);
	}
	else
		result = STATUS_ERROR;

	if (shadow_pass)
		pfree(shadow_pass);
	pfree(passwd);

	return result;
}