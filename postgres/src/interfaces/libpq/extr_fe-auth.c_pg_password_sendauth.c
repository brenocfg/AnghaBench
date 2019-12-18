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
struct TYPE_5__ {char* pguser; int /*<<< orphan*/  pversion; int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;
typedef  int AuthRequest ;

/* Variables and functions */
#define  AUTH_REQ_MD5 129 
#define  AUTH_REQ_PASSWORD 128 
 int /*<<< orphan*/  MD5_PASSWD_LEN ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int STATUS_ERROR ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  pg_md5_encrypt (char const*,char*,int,char*) ; 
 scalar_t__ pqGetnchar (char*,int,TYPE_1__*) ; 
 int pqPacketSend (TYPE_1__*,char,char const*,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
pg_password_sendauth(PGconn *conn, const char *password, AuthRequest areq)
{
	int			ret;
	char	   *crypt_pwd = NULL;
	const char *pwd_to_send;
	char		md5Salt[4];

	/* Read the salt from the AuthenticationMD5Password message. */
	if (areq == AUTH_REQ_MD5)
	{
		if (pqGetnchar(md5Salt, 4, conn))
			return STATUS_ERROR;	/* shouldn't happen */
	}

	/* Encrypt the password if needed. */

	switch (areq)
	{
		case AUTH_REQ_MD5:
			{
				char	   *crypt_pwd2;

				/* Allocate enough space for two MD5 hashes */
				crypt_pwd = malloc(2 * (MD5_PASSWD_LEN + 1));
				if (!crypt_pwd)
				{
					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext("out of memory\n"));
					return STATUS_ERROR;
				}

				crypt_pwd2 = crypt_pwd + MD5_PASSWD_LEN + 1;
				if (!pg_md5_encrypt(password, conn->pguser,
									strlen(conn->pguser), crypt_pwd2))
				{
					free(crypt_pwd);
					return STATUS_ERROR;
				}
				if (!pg_md5_encrypt(crypt_pwd2 + strlen("md5"), md5Salt,
									4, crypt_pwd))
				{
					free(crypt_pwd);
					return STATUS_ERROR;
				}

				pwd_to_send = crypt_pwd;
				break;
			}
		case AUTH_REQ_PASSWORD:
			pwd_to_send = password;
			break;
		default:
			return STATUS_ERROR;
	}
	/* Packet has a message type as of protocol 3.0 */
	if (PG_PROTOCOL_MAJOR(conn->pversion) >= 3)
		ret = pqPacketSend(conn, 'p', pwd_to_send, strlen(pwd_to_send) + 1);
	else
		ret = pqPacketSend(conn, 0, pwd_to_send, strlen(pwd_to_send) + 1);
	if (crypt_pwd)
		free(crypt_pwd);
	return ret;
}