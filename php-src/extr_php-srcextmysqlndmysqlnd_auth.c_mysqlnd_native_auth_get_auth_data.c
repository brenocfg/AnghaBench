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
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  int /*<<< orphan*/  zend_uchar ;
struct st_mysqlnd_authentication_plugin {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  error_info; } ;
typedef  int /*<<< orphan*/  MYSQLND_SESSION_OPTIONS ;
typedef  int /*<<< orphan*/  MYSQLND_PFC_DATA ;
typedef  TYPE_1__ MYSQLND_CONN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CR_MALFORMED_PACKET ; 
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_ERR_FMT (char*,size_t const,size_t const) ; 
 int /*<<< orphan*/  DBG_RETURN (int /*<<< orphan*/ *) ; 
 size_t const SCRAMBLE_LENGTH ; 
 int /*<<< orphan*/  SET_CLIENT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UNKNOWN_SQLSTATE ; 
 int /*<<< orphan*/ * malloc (size_t const) ; 
 int /*<<< orphan*/  php_mysqlnd_scramble (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 

__attribute__((used)) static zend_uchar *
mysqlnd_native_auth_get_auth_data(struct st_mysqlnd_authentication_plugin * self,
								  size_t * auth_data_len,
								  MYSQLND_CONN_DATA * conn, const char * const user, const char * const passwd,
								  const size_t passwd_len, zend_uchar * auth_plugin_data, const size_t auth_plugin_data_len,
								  const MYSQLND_SESSION_OPTIONS * const session_options,
								  const MYSQLND_PFC_DATA * const pfc_data,
								  const zend_ulong mysql_flags
								 )
{
	zend_uchar * ret = NULL;
	DBG_ENTER("mysqlnd_native_auth_get_auth_data");
	*auth_data_len = 0;

	/* 5.5.x reports 21 as scramble length because it needs to show the length of the data before the plugin name */
	if (auth_plugin_data_len < SCRAMBLE_LENGTH) {
		/* mysql_native_password only works with SCRAMBLE_LENGTH scramble */
		SET_CLIENT_ERROR(conn->error_info, CR_MALFORMED_PACKET, UNKNOWN_SQLSTATE, "The server sent wrong length for scramble");
		DBG_ERR_FMT("The server sent wrong length for scramble %u. Expected %u", auth_plugin_data_len, SCRAMBLE_LENGTH);
		DBG_RETURN(NULL);
	}

	/* copy scrambled pass*/
	if (passwd && passwd_len) {
		ret = malloc(SCRAMBLE_LENGTH);
		*auth_data_len = SCRAMBLE_LENGTH;
		/* In 4.1 we use CLIENT_SECURE_CONNECTION and thus the len of the buf should be passed */
		php_mysqlnd_scramble((zend_uchar*)ret, auth_plugin_data, (zend_uchar*)passwd, passwd_len);
	}
	DBG_RETURN(ret);
}