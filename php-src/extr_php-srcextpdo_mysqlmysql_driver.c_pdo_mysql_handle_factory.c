#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int zend_long ;
typedef  int /*<<< orphan*/  vars ;
struct pdo_data_src_parser {char* member_0; char* member_1; char* optval; scalar_t__ freeme; int /*<<< orphan*/  member_2; } ;
struct TYPE_9__ {int /*<<< orphan*/ * errmsg; scalar_t__ errcode; } ;
struct TYPE_10__ {int max_buffer_size; int assume_national_character_set_strings; int buffered; int emulate_prepare; int attached; int /*<<< orphan*/  server; TYPE_1__ einfo; } ;
typedef  TYPE_2__ pdo_mysql_db_handle ;
struct TYPE_11__ {int alloc_own_columns; int max_escaped_char_length; int /*<<< orphan*/ * methods; int /*<<< orphan*/  auto_commit; int /*<<< orphan*/  password; int /*<<< orphan*/  username; TYPE_2__* driver_data; int /*<<< orphan*/  is_persistent; int /*<<< orphan*/  data_source_len; int /*<<< orphan*/  data_source; } ;
typedef  TYPE_3__ pdo_dbh_t ;

/* Variables and functions */
 int CLIENT_FOUND_ROWS ; 
 int CLIENT_IGNORE_SPACE ; 
 int /*<<< orphan*/  MYSQL_INIT_COMMAND ; 
 int /*<<< orphan*/  MYSQL_OPT_COMPRESS ; 
 int /*<<< orphan*/  MYSQL_OPT_CONNECT_TIMEOUT ; 
 int /*<<< orphan*/  MYSQL_READ_DEFAULT_FILE ; 
 int /*<<< orphan*/  MYSQL_READ_DEFAULT_GROUP ; 
 int /*<<< orphan*/  PDO_ATTR_DEFAULT_STR_PARAM ; 
 int /*<<< orphan*/  PDO_ATTR_EMULATE_PREPARES ; 
 int /*<<< orphan*/  PDO_ATTR_TIMEOUT ; 
 int /*<<< orphan*/  PDO_DBG_ENTER (char*) ; 
 int /*<<< orphan*/  PDO_DBG_INF_FMT (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  PDO_DBG_RETURN (int) ; 
 char* PDO_DEFAULT_MYSQL_UNIX_ADDR ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_COMPRESS ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_DIRECT_QUERY ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_FOUND_ROWS ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_IGNORE_SPACE ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_INIT_COMMAND ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_LOCAL_INFILE ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_MAX_BUFFER_SIZE ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_READ_DEFAULT_FILE ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_READ_DEFAULT_GROUP ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_SSL_CA ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_SSL_CAPATH ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_SSL_CERT ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_SSL_CIPHER ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_SSL_KEY ; 
 int /*<<< orphan*/  PDO_MYSQL_ATTR_USE_BUFFERED_QUERY ; 
 int PDO_PARAM_STR_NATL ; 
 char* PG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZSTR_VAL (int /*<<< orphan*/ *) ; 
 unsigned int atoi (char*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  mysql_handle_autocommit (TYPE_3__*) ; 
 int /*<<< orphan*/  mysql_methods ; 
 scalar_t__ mysql_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * mysql_real_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,char*,int) ; 
 int /*<<< orphan*/  mysql_ssl_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_basedir ; 
 int pdo_attr_lval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pdo_attr_strval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdo_mysql_error (TYPE_3__*) ; 
 int /*<<< orphan*/  pdo_mysql_init (int /*<<< orphan*/ ) ; 
 TYPE_2__* pecalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_pdo_parse_data_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pdo_data_src_parser*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdo_mysql_handle_factory(pdo_dbh_t *dbh, zval *driver_options)
{
	pdo_mysql_db_handle *H;
	size_t i;
	int ret = 0;
	char *host = NULL, *unix_socket = NULL;
	unsigned int port = 3306;
	char *dbname;
	struct pdo_data_src_parser vars[] = {
		{ "charset",  NULL,	0 },
		{ "dbname",   "",	0 },
		{ "host",   "localhost",	0 },
		{ "port",   "3306",	0 },
		{ "unix_socket",  PDO_DEFAULT_MYSQL_UNIX_ADDR,	0 },
	};
	int connect_opts = 0
#ifdef CLIENT_MULTI_RESULTS
		|CLIENT_MULTI_RESULTS
#endif
		;
#if defined(PDO_USE_MYSQLND)
	size_t dbname_len = 0;
	size_t password_len = 0;
#endif

#ifdef CLIENT_MULTI_STATEMENTS
	if (!driver_options) {
		connect_opts |= CLIENT_MULTI_STATEMENTS;
	} else if (pdo_attr_lval(driver_options, PDO_MYSQL_ATTR_MULTI_STATEMENTS, 1)) {
		connect_opts |= CLIENT_MULTI_STATEMENTS;
	}
#endif

	PDO_DBG_ENTER("pdo_mysql_handle_factory");
	PDO_DBG_INF_FMT("dbh=%p", dbh);
#ifdef CLIENT_MULTI_RESULTS
	PDO_DBG_INF("multi results");
#endif

	php_pdo_parse_data_source(dbh->data_source, dbh->data_source_len, vars, 5);

	H = pecalloc(1, sizeof(pdo_mysql_db_handle), dbh->is_persistent);

	H->einfo.errcode = 0;
	H->einfo.errmsg = NULL;

	/* allocate an environment */

	/* handle for the server */
	if (!(H->server = pdo_mysql_init(dbh->is_persistent))) {
		pdo_mysql_error(dbh);
		goto cleanup;
	}
#if defined(PDO_USE_MYSQLND)
	if (dbh->is_persistent) {
		mysqlnd_restart_psession(H->server);
	}
#endif

	dbh->driver_data = H;

#ifndef PDO_USE_MYSQLND
	H->max_buffer_size = 1024*1024;
#endif

	H->assume_national_character_set_strings = 0;
	H->buffered = H->emulate_prepare = 1;

	/* handle MySQL options */
	if (driver_options) {
		zend_long connect_timeout = pdo_attr_lval(driver_options, PDO_ATTR_TIMEOUT, 30);
		zend_long local_infile = pdo_attr_lval(driver_options, PDO_MYSQL_ATTR_LOCAL_INFILE, 0);
		zend_string *init_cmd = NULL;
#ifndef PDO_USE_MYSQLND
		zend_string *default_file = NULL, *default_group = NULL;
#endif
		zend_long compress = 0;
		zend_string *ssl_key = NULL, *ssl_cert = NULL, *ssl_ca = NULL, *ssl_capath = NULL, *ssl_cipher = NULL;
		H->buffered = pdo_attr_lval(driver_options, PDO_MYSQL_ATTR_USE_BUFFERED_QUERY, 1);

		H->emulate_prepare = pdo_attr_lval(driver_options,
			PDO_MYSQL_ATTR_DIRECT_QUERY, H->emulate_prepare);
		H->emulate_prepare = pdo_attr_lval(driver_options,
			PDO_ATTR_EMULATE_PREPARES, H->emulate_prepare);

		H->assume_national_character_set_strings = pdo_attr_lval(driver_options,
			PDO_ATTR_DEFAULT_STR_PARAM, 0) == PDO_PARAM_STR_NATL;

#ifndef PDO_USE_MYSQLND
		H->max_buffer_size = pdo_attr_lval(driver_options, PDO_MYSQL_ATTR_MAX_BUFFER_SIZE, H->max_buffer_size);
#endif

		if (pdo_attr_lval(driver_options, PDO_MYSQL_ATTR_FOUND_ROWS, 0)) {
			connect_opts |= CLIENT_FOUND_ROWS;
		}

		if (pdo_attr_lval(driver_options, PDO_MYSQL_ATTR_IGNORE_SPACE, 0)) {
			connect_opts |= CLIENT_IGNORE_SPACE;
		}

		if (mysql_options(H->server, MYSQL_OPT_CONNECT_TIMEOUT, (const char *)&connect_timeout)) {
			pdo_mysql_error(dbh);
			goto cleanup;
		}

#ifndef PDO_USE_MYSQLND
		if (PG(open_basedir) && PG(open_basedir)[0] != '\0') {
			local_infile = 0;
		}
#endif
#if defined(MYSQL_OPT_LOCAL_INFILE) || defined(PDO_USE_MYSQLND)
		if (mysql_options(H->server, MYSQL_OPT_LOCAL_INFILE, (const char *)&local_infile)) {
			pdo_mysql_error(dbh);
			goto cleanup;
		}
#endif
#ifdef MYSQL_OPT_RECONNECT
		/* since 5.0.3, the default for this option is 0 if not specified.
		 * we want the old behaviour
		 * mysqlnd doesn't support reconnect, thus we don't have "|| defined(PDO_USE_MYSQLND)"
		*/
		{
			zend_long reconnect = 1;
			mysql_options(H->server, MYSQL_OPT_RECONNECT, (const char*)&reconnect);
		}
#endif
		init_cmd = pdo_attr_strval(driver_options, PDO_MYSQL_ATTR_INIT_COMMAND, NULL);
		if (init_cmd) {
			if (mysql_options(H->server, MYSQL_INIT_COMMAND, (const char *)ZSTR_VAL(init_cmd))) {
				zend_string_release_ex(init_cmd, 0);
				pdo_mysql_error(dbh);
				goto cleanup;
			}
			zend_string_release_ex(init_cmd, 0);
		}
#ifndef PDO_USE_MYSQLND
		default_file = pdo_attr_strval(driver_options, PDO_MYSQL_ATTR_READ_DEFAULT_FILE, NULL);
		if (default_file) {
			if (mysql_options(H->server, MYSQL_READ_DEFAULT_FILE, (const char *)ZSTR_VAL(default_file))) {
				zend_string_release_ex(default_file, 0);
				pdo_mysql_error(dbh);
				goto cleanup;
			}
			zend_string_release_ex(default_file, 0);
		}

		default_group = pdo_attr_strval(driver_options, PDO_MYSQL_ATTR_READ_DEFAULT_GROUP, NULL);
		if (default_group) {
			if (mysql_options(H->server, MYSQL_READ_DEFAULT_GROUP, (const char *)ZSTR_VAL(default_group))) {
				zend_string_release_ex(default_group, 0);
				pdo_mysql_error(dbh);
				goto cleanup;
			}
			zend_string_release_ex(default_group, 0);
		}
#endif
		compress = pdo_attr_lval(driver_options, PDO_MYSQL_ATTR_COMPRESS, 0);
		if (compress) {
			if (mysql_options(H->server, MYSQL_OPT_COMPRESS, 0)) {
				pdo_mysql_error(dbh);
				goto cleanup;
			}
		}

		ssl_key = pdo_attr_strval(driver_options, PDO_MYSQL_ATTR_SSL_KEY, NULL);
		ssl_cert = pdo_attr_strval(driver_options, PDO_MYSQL_ATTR_SSL_CERT, NULL);
		ssl_ca = pdo_attr_strval(driver_options, PDO_MYSQL_ATTR_SSL_CA, NULL);
		ssl_capath = pdo_attr_strval(driver_options, PDO_MYSQL_ATTR_SSL_CAPATH, NULL);
		ssl_cipher = pdo_attr_strval(driver_options, PDO_MYSQL_ATTR_SSL_CIPHER, NULL);

		if (ssl_key || ssl_cert || ssl_ca || ssl_capath || ssl_cipher) {
			mysql_ssl_set(H->server,
					ssl_key? ZSTR_VAL(ssl_key) : NULL,
					ssl_cert? ZSTR_VAL(ssl_cert) : NULL,
					ssl_ca? ZSTR_VAL(ssl_ca) : NULL,
					ssl_capath? ZSTR_VAL(ssl_capath) : NULL,
					ssl_cipher? ZSTR_VAL(ssl_cipher) : NULL);
			if (ssl_key) {
				zend_string_release_ex(ssl_key, 0);
			}
			if (ssl_cert) {
				zend_string_release_ex(ssl_cert, 0);
			}
			if (ssl_ca) {
				zend_string_release_ex(ssl_ca, 0);
			}
			if (ssl_capath) {
				zend_string_release_ex(ssl_capath, 0);
			}
			if (ssl_cipher) {
				zend_string_release_ex(ssl_cipher, 0);
			}
		}

#if MYSQL_VERSION_ID > 50605 || defined(PDO_USE_MYSQLND)
		{
			zend_string *public_key = pdo_attr_strval(driver_options, PDO_MYSQL_ATTR_SERVER_PUBLIC_KEY, NULL);
			if (public_key) {
				if (mysql_options(H->server, MYSQL_SERVER_PUBLIC_KEY, ZSTR_VAL(public_key))) {
					pdo_mysql_error(dbh);
					zend_string_release_ex(public_key, 0);
					goto cleanup;
				}
				zend_string_release_ex(public_key, 0);
			}
		}
#endif

#ifdef PDO_USE_MYSQLND
		{
			zend_long ssl_verify_cert = pdo_attr_lval(driver_options,
					PDO_MYSQL_ATTR_SSL_VERIFY_SERVER_CERT, -1);
			if (ssl_verify_cert != -1) {
				connect_opts |= ssl_verify_cert ?
					CLIENT_SSL_VERIFY_SERVER_CERT:
					CLIENT_SSL_DONT_VERIFY_SERVER_CERT;
			}
		}
#endif
	} else {
#if defined(MYSQL_OPT_LOCAL_INFILE) || defined(PDO_USE_MYSQLND)
		// in case there are no driver options disable 'local infile' explicitly
		zend_long local_infile = 0;
		if (mysql_options(H->server, MYSQL_OPT_LOCAL_INFILE, (const char *)&local_infile)) {
			pdo_mysql_error(dbh);
			goto cleanup;
		}
#endif
	}

#ifdef PDO_MYSQL_HAS_CHARSET
	if (vars[0].optval && mysql_options(H->server, MYSQL_SET_CHARSET_NAME, vars[0].optval)) {
		pdo_mysql_error(dbh);
		goto cleanup;
	}
#endif

	dbname = vars[1].optval;
	host = vars[2].optval;
	if(vars[3].optval) {
		port = atoi(vars[3].optval);
	}

#ifdef PHP_WIN32
	if (vars[2].optval && !strcmp(".", vars[2].optval)) {
#else
	if (vars[2].optval && !strcmp("localhost", vars[2].optval)) {
#endif
		unix_socket = vars[4].optval;
	}

	/* TODO: - Check zval cache + ZTS */
#ifdef PDO_USE_MYSQLND
	if (dbname) {
		dbname_len = strlen(dbname);
	}

	if (dbh->password) {
		password_len = strlen(dbh->password);
	}

	if (mysqlnd_connect(H->server, host, dbh->username, dbh->password, password_len, dbname, dbname_len,
						port, unix_socket, connect_opts, MYSQLND_CLIENT_NO_FLAG) == NULL) {
#else
	if (mysql_real_connect(H->server, host, dbh->username, dbh->password, dbname, port, unix_socket, connect_opts) == NULL) {
#endif
		pdo_mysql_error(dbh);
		goto cleanup;
	}

	if (!dbh->auto_commit) {
		mysql_handle_autocommit(dbh);
	}

	H->attached = 1;

	dbh->alloc_own_columns = 1;
	dbh->max_escaped_char_length = 2;
	dbh->methods = &mysql_methods;

	ret = 1;

cleanup:
	for (i = 0; i < sizeof(vars)/sizeof(vars[0]); i++) {
		if (vars[i].freeme) {
			efree(vars[i].optval);
		}
	}

	dbh->methods = &mysql_methods;

	PDO_DBG_RETURN(ret);
}