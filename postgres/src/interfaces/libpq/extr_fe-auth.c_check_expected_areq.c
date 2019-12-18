#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* channel_binding; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  sasl_state; } ;
typedef  TYPE_1__ PGconn ;
typedef  int AuthRequest ;

/* Variables and functions */
#define  AUTH_REQ_OK 131 
#define  AUTH_REQ_SASL 130 
#define  AUTH_REQ_SASL_CONT 129 
#define  AUTH_REQ_SASL_FIN 128 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  pg_fe_scram_channel_bound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
check_expected_areq(AuthRequest areq, PGconn *conn)
{
	bool		result = true;

	/*
	 * When channel_binding=require, we must protect against two cases: (1) we
	 * must not respond to non-SASL authentication requests, which might leak
	 * information such as the client's password; and (2) even if we receive
	 * AUTH_REQ_OK, we still must ensure that channel binding has happened in
	 * order to authenticate the server.
	 */
	if (conn->channel_binding[0] == 'r' /* require */ )
	{
		switch (areq)
		{
			case AUTH_REQ_SASL:
			case AUTH_REQ_SASL_CONT:
			case AUTH_REQ_SASL_FIN:
				break;
			case AUTH_REQ_OK:
				if (!pg_fe_scram_channel_bound(conn->sasl_state))
				{
					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext("Channel binding required, but server authenticated client without channel binding\n"));
					result = false;
				}
				break;
			default:
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("Channel binding required but not supported by server's authentication request\n"));
				result = false;
				break;
		}
	}

	return result;
}