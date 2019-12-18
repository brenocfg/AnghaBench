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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  sebuf ;
typedef  int /*<<< orphan*/  homedir ;
typedef  int /*<<< orphan*/  fnbuf ;
typedef  int /*<<< orphan*/  X509_STORE ;
struct TYPE_5__ {char* sslcert; char* sslkey; char* sslrootcert; char* sslcrl; char* sslmode; int ssl_in_use; int /*<<< orphan*/  ssl; int /*<<< orphan*/ * sslcompression; int /*<<< orphan*/  errorMessage; int /*<<< orphan*/ * engine; int /*<<< orphan*/  sock; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  TYPE_1__ PGconn ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/ * ENGINE_by_id (char*) ; 
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ENGINE_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_load_private_key (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int MAXPGPATH ; 
 int PG_STRERROR_R_BUFLEN ; 
 char* ROOT_CERT_FILE ; 
 char* ROOT_CRL_FILE ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_get_cert_store (int /*<<< orphan*/ *) ; 
 int SSL_CTX_load_verify_locations (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER ; 
 int /*<<< orphan*/  SSL_OP_NO_COMPRESSION ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int SSL_check_private_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_clear_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_app_data (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_set_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SSL_use_PrivateKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SSL_use_PrivateKey_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLerrfree (char*) ; 
 char* SSLerrmessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLv23_method () ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 char* USER_CERT_FILE ; 
 char* USER_KEY_FILE ; 
 int X509_STORE_load_locations (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_set_flags (int /*<<< orphan*/ *,int) ; 
 int X509_V_FLAG_CRL_CHECK ; 
 int X509_V_FLAG_CRL_CHECK_ALL ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  my_SSL_set_fd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pqGetHomeDirectory (char*,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 char* strerror_r (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  verify_cb ; 

__attribute__((used)) static int
initialize_SSL(PGconn *conn)
{
	SSL_CTX    *SSL_context;
	struct stat buf;
	char		homedir[MAXPGPATH];
	char		fnbuf[MAXPGPATH];
	char		sebuf[PG_STRERROR_R_BUFLEN];
	bool		have_homedir;
	bool		have_cert;
	bool		have_rootcert;
	EVP_PKEY   *pkey = NULL;

	/*
	 * We'll need the home directory if any of the relevant parameters are
	 * defaulted.  If pqGetHomeDirectory fails, act as though none of the
	 * files could be found.
	 */
	if (!(conn->sslcert && strlen(conn->sslcert) > 0) ||
		!(conn->sslkey && strlen(conn->sslkey) > 0) ||
		!(conn->sslrootcert && strlen(conn->sslrootcert) > 0) ||
		!(conn->sslcrl && strlen(conn->sslcrl) > 0))
		have_homedir = pqGetHomeDirectory(homedir, sizeof(homedir));
	else						/* won't need it */
		have_homedir = false;

	/*
	 * Create a new SSL_CTX object.
	 *
	 * We used to share a single SSL_CTX between all connections, but it was
	 * complicated if connections used different certificates. So now we
	 * create a separate context for each connection, and accept the overhead.
	 */
	SSL_context = SSL_CTX_new(SSLv23_method());
	if (!SSL_context)
	{
		char	   *err = SSLerrmessage(ERR_get_error());

		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("could not create SSL context: %s\n"),
						  err);
		SSLerrfree(err);
		return -1;
	}

	/* Disable old protocol versions */
	SSL_CTX_set_options(SSL_context, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

	/*
	 * Disable OpenSSL's moving-write-buffer sanity check, because it causes
	 * unnecessary failures in nonblocking send cases.
	 */
	SSL_CTX_set_mode(SSL_context, SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER);

	/*
	 * If the root cert file exists, load it so we can perform certificate
	 * verification. If sslmode is "verify-full" we will also do further
	 * verification after the connection has been completed.
	 */
	if (conn->sslrootcert && strlen(conn->sslrootcert) > 0)
		strlcpy(fnbuf, conn->sslrootcert, sizeof(fnbuf));
	else if (have_homedir)
		snprintf(fnbuf, sizeof(fnbuf), "%s/%s", homedir, ROOT_CERT_FILE);
	else
		fnbuf[0] = '\0';

	if (fnbuf[0] != '\0' &&
		stat(fnbuf, &buf) == 0)
	{
		X509_STORE *cvstore;

		if (SSL_CTX_load_verify_locations(SSL_context, fnbuf, NULL) != 1)
		{
			char	   *err = SSLerrmessage(ERR_get_error());

			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("could not read root certificate file \"%s\": %s\n"),
							  fnbuf, err);
			SSLerrfree(err);
			SSL_CTX_free(SSL_context);
			return -1;
		}

		if ((cvstore = SSL_CTX_get_cert_store(SSL_context)) != NULL)
		{
			if (conn->sslcrl && strlen(conn->sslcrl) > 0)
				strlcpy(fnbuf, conn->sslcrl, sizeof(fnbuf));
			else if (have_homedir)
				snprintf(fnbuf, sizeof(fnbuf), "%s/%s", homedir, ROOT_CRL_FILE);
			else
				fnbuf[0] = '\0';

			/* Set the flags to check against the complete CRL chain */
			if (fnbuf[0] != '\0' &&
				X509_STORE_load_locations(cvstore, fnbuf, NULL) == 1)
			{
				X509_STORE_set_flags(cvstore,
									 X509_V_FLAG_CRL_CHECK | X509_V_FLAG_CRL_CHECK_ALL);
			}
			/* if not found, silently ignore;  we do not require CRL */
			ERR_clear_error();
		}
		have_rootcert = true;
	}
	else
	{
		/*
		 * stat() failed; assume root file doesn't exist.  If sslmode is
		 * verify-ca or verify-full, this is an error.  Otherwise, continue
		 * without performing any server cert verification.
		 */
		if (conn->sslmode[0] == 'v')	/* "verify-ca" or "verify-full" */
		{
			/*
			 * The only way to reach here with an empty filename is if
			 * pqGetHomeDirectory failed.  That's a sufficiently unusual case
			 * that it seems worth having a specialized error message for it.
			 */
			if (fnbuf[0] == '\0')
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("could not get home directory to locate root certificate file\n"
												"Either provide the file or change sslmode to disable server certificate verification.\n"));
			else
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("root certificate file \"%s\" does not exist\n"
												"Either provide the file or change sslmode to disable server certificate verification.\n"), fnbuf);
			SSL_CTX_free(SSL_context);
			return -1;
		}
		have_rootcert = false;
	}

	/* Read the client certificate file */
	if (conn->sslcert && strlen(conn->sslcert) > 0)
		strlcpy(fnbuf, conn->sslcert, sizeof(fnbuf));
	else if (have_homedir)
		snprintf(fnbuf, sizeof(fnbuf), "%s/%s", homedir, USER_CERT_FILE);
	else
		fnbuf[0] = '\0';

	if (fnbuf[0] == '\0')
	{
		/* no home directory, proceed without a client cert */
		have_cert = false;
	}
	else if (stat(fnbuf, &buf) != 0)
	{
		/*
		 * If file is not present, just go on without a client cert; server
		 * might or might not accept the connection.  Any other error,
		 * however, is grounds for complaint.
		 */
		if (errno != ENOENT && errno != ENOTDIR)
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("could not open certificate file \"%s\": %s\n"),
							  fnbuf, strerror_r(errno, sebuf, sizeof(sebuf)));
			SSL_CTX_free(SSL_context);
			return -1;
		}
		have_cert = false;
	}
	else
	{
		/*
		 * Cert file exists, so load it. Since OpenSSL doesn't provide the
		 * equivalent of "SSL_use_certificate_chain_file", we have to load it
		 * into the SSL context, rather than the SSL object.
		 */
		if (SSL_CTX_use_certificate_chain_file(SSL_context, fnbuf) != 1)
		{
			char	   *err = SSLerrmessage(ERR_get_error());

			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("could not read certificate file \"%s\": %s\n"),
							  fnbuf, err);
			SSLerrfree(err);
			SSL_CTX_free(SSL_context);
			return -1;
		}

		/* need to load the associated private key, too */
		have_cert = true;
	}

	/*
	 * The SSL context is now loaded with the correct root and client
	 * certificates. Create a connection-specific SSL object. The private key
	 * is loaded directly into the SSL object. (We could load the private key
	 * into the context, too, but we have done it this way historically, and
	 * it doesn't really matter.)
	 */
	if (!(conn->ssl = SSL_new(SSL_context)) ||
		!SSL_set_app_data(conn->ssl, conn) ||
		!my_SSL_set_fd(conn, conn->sock))
	{
		char	   *err = SSLerrmessage(ERR_get_error());

		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("could not establish SSL connection: %s\n"),
						  err);
		SSLerrfree(err);
		SSL_CTX_free(SSL_context);
		return -1;
	}
	conn->ssl_in_use = true;

	/*
	 * SSL contexts are reference counted by OpenSSL. We can free it as soon
	 * as we have created the SSL object, and it will stick around for as long
	 * as it's actually needed.
	 */
	SSL_CTX_free(SSL_context);
	SSL_context = NULL;

	/*
	 * Read the SSL key. If a key is specified, treat it as an engine:key
	 * combination if there is colon present - we don't support files with
	 * colon in the name. The exception is if the second character is a colon,
	 * in which case it can be a Windows filename with drive specification.
	 */
	if (have_cert && conn->sslkey && strlen(conn->sslkey) > 0)
	{
#ifdef USE_SSL_ENGINE
		if (strchr(conn->sslkey, ':')
#ifdef WIN32
			&& conn->sslkey[1] != ':'
#endif
			)
		{
			/* Colon, but not in second character, treat as engine:key */
			char	   *engine_str = strdup(conn->sslkey);
			char	   *engine_colon;

			if (engine_str == NULL)
			{
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("out of memory\n"));
				return -1;
			}

			/* cannot return NULL because we already checked before strdup */
			engine_colon = strchr(engine_str, ':');

			*engine_colon = '\0';	/* engine_str now has engine name */
			engine_colon++;		/* engine_colon now has key name */

			conn->engine = ENGINE_by_id(engine_str);
			if (conn->engine == NULL)
			{
				char	   *err = SSLerrmessage(ERR_get_error());

				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("could not load SSL engine \"%s\": %s\n"),
								  engine_str, err);
				SSLerrfree(err);
				free(engine_str);
				return -1;
			}

			if (ENGINE_init(conn->engine) == 0)
			{
				char	   *err = SSLerrmessage(ERR_get_error());

				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("could not initialize SSL engine \"%s\": %s\n"),
								  engine_str, err);
				SSLerrfree(err);
				ENGINE_free(conn->engine);
				conn->engine = NULL;
				free(engine_str);
				return -1;
			}

			pkey = ENGINE_load_private_key(conn->engine, engine_colon,
										   NULL, NULL);
			if (pkey == NULL)
			{
				char	   *err = SSLerrmessage(ERR_get_error());

				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("could not read private SSL key \"%s\" from engine \"%s\": %s\n"),
								  engine_colon, engine_str, err);
				SSLerrfree(err);
				ENGINE_finish(conn->engine);
				ENGINE_free(conn->engine);
				conn->engine = NULL;
				free(engine_str);
				return -1;
			}
			if (SSL_use_PrivateKey(conn->ssl, pkey) != 1)
			{
				char	   *err = SSLerrmessage(ERR_get_error());

				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("could not load private SSL key \"%s\" from engine \"%s\": %s\n"),
								  engine_colon, engine_str, err);
				SSLerrfree(err);
				ENGINE_finish(conn->engine);
				ENGINE_free(conn->engine);
				conn->engine = NULL;
				free(engine_str);
				return -1;
			}

			free(engine_str);

			fnbuf[0] = '\0';	/* indicate we're not going to load from a
								 * file */
		}
		else
#endif							/* USE_SSL_ENGINE */
		{
			/* PGSSLKEY is not an engine, treat it as a filename */
			strlcpy(fnbuf, conn->sslkey, sizeof(fnbuf));
		}
	}
	else if (have_homedir)
	{
		/* No PGSSLKEY specified, load default file */
		snprintf(fnbuf, sizeof(fnbuf), "%s/%s", homedir, USER_KEY_FILE);
	}
	else
		fnbuf[0] = '\0';

	if (have_cert && fnbuf[0] != '\0')
	{
		/* read the client key from file */

		if (stat(fnbuf, &buf) != 0)
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("certificate present, but not private key file \"%s\"\n"),
							  fnbuf);
			return -1;
		}
#ifndef WIN32
		if (!S_ISREG(buf.st_mode) || buf.st_mode & (S_IRWXG | S_IRWXO))
		{
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("private key file \"%s\" has group or world access; permissions should be u=rw (0600) or less\n"),
							  fnbuf);
			return -1;
		}
#endif

		if (SSL_use_PrivateKey_file(conn->ssl, fnbuf, SSL_FILETYPE_PEM) != 1)
		{
			char	   *err = SSLerrmessage(ERR_get_error());

			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("could not load private key file \"%s\": %s\n"),
							  fnbuf, err);
			SSLerrfree(err);
			return -1;
		}
	}

	/* verify that the cert and key go together */
	if (have_cert &&
		SSL_check_private_key(conn->ssl) != 1)
	{
		char	   *err = SSLerrmessage(ERR_get_error());

		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("certificate does not match private key file \"%s\": %s\n"),
						  fnbuf, err);
		SSLerrfree(err);
		return -1;
	}

	/*
	 * If a root cert was loaded, also set our certificate verification
	 * callback.
	 */
	if (have_rootcert)
		SSL_set_verify(conn->ssl, SSL_VERIFY_PEER, verify_cb);

	/*
	 * Set compression option if the OpenSSL version used supports it (from
	 * 1.0.0 on).
	 */
#ifdef SSL_OP_NO_COMPRESSION
	if (conn->sslcompression && conn->sslcompression[0] == '0')
		SSL_set_options(conn->ssl, SSL_OP_NO_COMPRESSION);

	/*
	 * Mainline OpenSSL introduced SSL_clear_options() before
	 * SSL_OP_NO_COMPRESSION, so this following #ifdef should not be
	 * necessary, but some old NetBSD version have a locally modified libssl
	 * that has SSL_OP_NO_COMPRESSION but not SSL_clear_options().
	 */
#ifdef HAVE_SSL_CLEAR_OPTIONS
	else
		SSL_clear_options(conn->ssl, SSL_OP_NO_COMPRESSION);
#endif
#endif

	return 0;
}