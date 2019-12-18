#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char zend_string ;
typedef  scalar_t__ time_t ;
struct timeval {int tv_sec; } ;
struct TYPE_8__ {char* s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ smart_str ;

/* Variables and functions */
 char* COOKIE_DOMAIN ; 
 char* COOKIE_EXPIRES ; 
 char* COOKIE_HTTPONLY ; 
 char* COOKIE_MAX_AGE ; 
 char* COOKIE_PATH ; 
 char* COOKIE_SAMESITE ; 
 char* COOKIE_SECURE ; 
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 char* PS (int /*<<< orphan*/ ) ; 
 scalar_t__ SG (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int ZSTR_LEN (char*) ; 
 char* ZSTR_VAL (char*) ; 
 int /*<<< orphan*/  cookie_domain ; 
 int /*<<< orphan*/  cookie_httponly ; 
 int /*<<< orphan*/  cookie_lifetime ; 
 int /*<<< orphan*/  cookie_path ; 
 int /*<<< orphan*/  cookie_samesite ; 
 int /*<<< orphan*/  cookie_secure ; 
 int /*<<< orphan*/  estrndup (char*,int) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  headers_sent ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 char* php_format_date (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 char* php_output_get_start_filename () ; 
 int php_output_get_start_lineno () ; 
 int /*<<< orphan*/  php_session_remove_cookie () ; 
 char* php_url_encode (char*,int) ; 
 int /*<<< orphan*/  sapi_add_header_ex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_name ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  smart_str_append_long (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  smart_str_appendl (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_1__*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  zend_string_release_ex (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_session_send_cookie(void) /* {{{ */
{
	smart_str ncookie = {0};
	zend_string *date_fmt = NULL;
	zend_string *e_session_name, *e_id;

	if (SG(headers_sent)) {
		const char *output_start_filename = php_output_get_start_filename();
		int output_start_lineno = php_output_get_start_lineno();

		if (output_start_filename) {
			php_error_docref(NULL, E_WARNING, "Cannot send session cookie - headers already sent by (output started at %s:%d)", output_start_filename, output_start_lineno);
		} else {
			php_error_docref(NULL, E_WARNING, "Cannot send session cookie - headers already sent");
		}
		return FAILURE;
	}

	/* URL encode session_name and id because they might be user supplied */
	e_session_name = php_url_encode(PS(session_name), strlen(PS(session_name)));
	e_id = php_url_encode(ZSTR_VAL(PS(id)), ZSTR_LEN(PS(id)));

	smart_str_appendl(&ncookie, "Set-Cookie: ", sizeof("Set-Cookie: ")-1);
	smart_str_appendl(&ncookie, ZSTR_VAL(e_session_name), ZSTR_LEN(e_session_name));
	smart_str_appendc(&ncookie, '=');
	smart_str_appendl(&ncookie, ZSTR_VAL(e_id), ZSTR_LEN(e_id));

	zend_string_release_ex(e_session_name, 0);
	zend_string_release_ex(e_id, 0);

	if (PS(cookie_lifetime) > 0) {
		struct timeval tv;
		time_t t;

		gettimeofday(&tv, NULL);
		t = tv.tv_sec + PS(cookie_lifetime);

		if (t > 0) {
			date_fmt = php_format_date("D, d-M-Y H:i:s T", sizeof("D, d-M-Y H:i:s T")-1, t, 0);
			smart_str_appends(&ncookie, COOKIE_EXPIRES);
			smart_str_appendl(&ncookie, ZSTR_VAL(date_fmt), ZSTR_LEN(date_fmt));
			zend_string_release_ex(date_fmt, 0);

			smart_str_appends(&ncookie, COOKIE_MAX_AGE);
			smart_str_append_long(&ncookie, PS(cookie_lifetime));
		}
	}

	if (PS(cookie_path)[0]) {
		smart_str_appends(&ncookie, COOKIE_PATH);
		smart_str_appends(&ncookie, PS(cookie_path));
	}

	if (PS(cookie_domain)[0]) {
		smart_str_appends(&ncookie, COOKIE_DOMAIN);
		smart_str_appends(&ncookie, PS(cookie_domain));
	}

	if (PS(cookie_secure)) {
		smart_str_appends(&ncookie, COOKIE_SECURE);
	}

	if (PS(cookie_httponly)) {
		smart_str_appends(&ncookie, COOKIE_HTTPONLY);
	}

	if (PS(cookie_samesite)[0]) {
    	smart_str_appends(&ncookie, COOKIE_SAMESITE);
    	smart_str_appends(&ncookie, PS(cookie_samesite));
    }

	smart_str_0(&ncookie);

	php_session_remove_cookie(); /* remove already sent session ID cookie */
	/*	'replace' must be 0 here, else a previous Set-Cookie
		header, probably sent with setcookie() will be replaced! */
	sapi_add_header_ex(estrndup(ZSTR_VAL(ncookie.s), ZSTR_LEN(ncookie.s)), ZSTR_LEN(ncookie.s), 0, 0);
	smart_str_free(&ncookie);

	return SUCCESS;
}