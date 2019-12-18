#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  int /*<<< orphan*/  zend_uchar ;
struct st_mysqlnd_authentication_plugin {int dummy; } ;
typedef  int /*<<< orphan*/  MYSQLND_SESSION_OPTIONS ;
typedef  int /*<<< orphan*/  MYSQLND_PFC_DATA ;
typedef  int /*<<< orphan*/  MYSQLND_CONN_DATA ;

/* Variables and functions */
 scalar_t__ zend_strndup (char const* const,size_t const) ; 

__attribute__((used)) static zend_uchar *
mysqlnd_pam_auth_get_auth_data(struct st_mysqlnd_authentication_plugin * self,
							   size_t * auth_data_len,
							   MYSQLND_CONN_DATA * conn, const char * const user, const char * const passwd,
							   const size_t passwd_len, zend_uchar * auth_plugin_data, const size_t auth_plugin_data_len,
							   const MYSQLND_SESSION_OPTIONS * const session_options,
							   const MYSQLND_PFC_DATA * const pfc_data,
							   const zend_ulong mysql_flags
							  )
{
	zend_uchar * ret = NULL;

	/* copy pass*/
	if (passwd && passwd_len) {
		ret = (zend_uchar*) zend_strndup(passwd, passwd_len);
	}
	*auth_data_len = passwd_len;

	return ret;
}