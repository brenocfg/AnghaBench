#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  errorMessage; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int MAX_ALGORITHM_NAME_LEN ; 
 scalar_t__ MD5_PASSWD_LEN ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (TYPE_1__*,char*) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 char* malloc (scalar_t__) ; 
 char* pg_fe_scram_build_secret (char const*) ; 
 int /*<<< orphan*/  pg_md5_encrypt (char const*,char const*,int,char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 

char *
PQencryptPasswordConn(PGconn *conn, const char *passwd, const char *user,
					  const char *algorithm)
{
#define MAX_ALGORITHM_NAME_LEN 50
	char		algobuf[MAX_ALGORITHM_NAME_LEN + 1];
	char	   *crypt_pwd = NULL;

	if (!conn)
		return NULL;

	/* If no algorithm was given, ask the server. */
	if (algorithm == NULL)
	{
		PGresult   *res;
		char	   *val;

		res = PQexec(conn, "show password_encryption");
		if (res == NULL)
		{
			/* PQexec() should've set conn->errorMessage already */
			return NULL;
		}
		if (PQresultStatus(res) != PGRES_TUPLES_OK)
		{
			/* PQexec() should've set conn->errorMessage already */
			PQclear(res);
			return NULL;
		}
		if (PQntuples(res) != 1 || PQnfields(res) != 1)
		{
			PQclear(res);
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("unexpected shape of result set returned for SHOW\n"));
			return NULL;
		}
		val = PQgetvalue(res, 0, 0);

		if (strlen(val) > MAX_ALGORITHM_NAME_LEN)
		{
			PQclear(res);
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("password_encryption value too long\n"));
			return NULL;
		}
		strcpy(algobuf, val);
		PQclear(res);

		algorithm = algobuf;
	}

	/*
	 * Also accept "on" and "off" as aliases for "md5", because
	 * password_encryption was a boolean before PostgreSQL 10.  We refuse to
	 * send the password in plaintext even if it was "off".
	 */
	if (strcmp(algorithm, "on") == 0 ||
		strcmp(algorithm, "off") == 0)
		algorithm = "md5";

	/*
	 * Ok, now we know what algorithm to use
	 */
	if (strcmp(algorithm, "scram-sha-256") == 0)
	{
		crypt_pwd = pg_fe_scram_build_secret(passwd);
	}
	else if (strcmp(algorithm, "md5") == 0)
	{
		crypt_pwd = malloc(MD5_PASSWD_LEN + 1);
		if (crypt_pwd)
		{
			if (!pg_md5_encrypt(passwd, user, strlen(user), crypt_pwd))
			{
				free(crypt_pwd);
				crypt_pwd = NULL;
			}
		}
	}
	else
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("unrecognized password encryption algorithm \"%s\"\n"),
						  algorithm);
		return NULL;
	}

	if (!crypt_pwd)
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("out of memory\n"));

	return crypt_pwd;
}