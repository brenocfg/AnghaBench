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

/* Variables and functions */
 int IS_LONG ; 
 int IS_NULL ; 
 int IS_STRING ; 
#define  MYSQL_INIT_COMMAND 141 
#define  MYSQL_OPT_CONNECT_TIMEOUT 140 
#define  MYSQL_OPT_GUESS_CONNECTION 139 
#define  MYSQL_OPT_LOCAL_INFILE 138 
#define  MYSQL_OPT_NAMED_PIPE 137 
#define  MYSQL_OPT_READ_TIMEOUT 136 
#define  MYSQL_OPT_USE_EMBEDDED_CONNECTION 135 
#define  MYSQL_OPT_USE_REMOTE_CONNECTION 134 
#define  MYSQL_OPT_WRITE_TIMEOUT 133 
#define  MYSQL_READ_DEFAULT_FILE 132 
#define  MYSQL_READ_DEFAULT_GROUP 131 
#define  MYSQL_SECURE_AUTH 130 
#define  MYSQL_SET_CHARSET_DIR 129 
#define  MYSQL_SET_CHARSET_NAME 128 

__attribute__((used)) static int mysqli_options_get_option_zval_type(int option)
{
	switch (option) {
#ifdef MYSQLI_USE_MYSQLND
		case MYSQLND_OPT_NET_CMD_BUFFER_SIZE:
		case MYSQLND_OPT_NET_READ_BUFFER_SIZE:
#ifdef MYSQLND_STRING_TO_INT_CONVERSION
		case MYSQLND_OPT_INT_AND_FLOAT_NATIVE:
#endif
#endif /* MYSQLI_USE_MYSQLND */
		case MYSQL_OPT_CONNECT_TIMEOUT:
#ifdef MYSQL_REPORT_DATA_TRUNCATION
		case MYSQL_REPORT_DATA_TRUNCATION:
#endif
		case MYSQL_OPT_LOCAL_INFILE:
		case MYSQL_OPT_NAMED_PIPE:
#ifdef MYSQL_OPT_PROTOCOL
                case MYSQL_OPT_PROTOCOL:
#endif /* MySQL 4.1.0 */
		case MYSQL_OPT_READ_TIMEOUT:
		case MYSQL_OPT_WRITE_TIMEOUT:
		case MYSQL_OPT_GUESS_CONNECTION:
		case MYSQL_OPT_USE_EMBEDDED_CONNECTION:
		case MYSQL_OPT_USE_REMOTE_CONNECTION:
		case MYSQL_SECURE_AUTH:
#ifdef MYSQL_OPT_RECONNECT
		case MYSQL_OPT_RECONNECT:
#endif /* MySQL 5.0.13 */
#ifdef MYSQL_OPT_SSL_VERIFY_SERVER_CERT
		case MYSQL_OPT_SSL_VERIFY_SERVER_CERT:
#endif /* MySQL 5.0.23 */
#ifdef MYSQL_OPT_COMPRESS
		case MYSQL_OPT_COMPRESS:
#endif /* mysqlnd @ PHP 5.3.2 */
#ifdef MYSQL_OPT_SSL_VERIFY_SERVER_CERT
	REGISTER_LONG_CONSTANT("MYSQLI_OPT_SSL_VERIFY_SERVER_CERT", MYSQL_OPT_SSL_VERIFY_SERVER_CERT, CONST_CS | CONST_PERSISTENT);
#endif /* MySQL 5.1.1., mysqlnd @ PHP 5.3.3 */
#if (MYSQL_VERSION_ID >= 50611 && defined(CLIENT_CAN_HANDLE_EXPIRED_PASSWORDS)) || defined(MYSQLI_USE_MYSQLND)
		case MYSQL_OPT_CAN_HANDLE_EXPIRED_PASSWORDS:
#endif
			return IS_LONG;

#ifdef MYSQL_SHARED_MEMORY_BASE_NAME
                case MYSQL_SHARED_MEMORY_BASE_NAME:
#endif /* MySQL 4.1.0 */
#ifdef MYSQL_SET_CLIENT_IP
		case MYSQL_SET_CLIENT_IP:
#endif /* MySQL 4.1.1 */
		case MYSQL_READ_DEFAULT_FILE:
		case MYSQL_READ_DEFAULT_GROUP:
		case MYSQL_INIT_COMMAND:
		case MYSQL_SET_CHARSET_NAME:
		case MYSQL_SET_CHARSET_DIR:
#if MYSQL_VERSION_ID > 50605 || defined(MYSQLI_USE_MYSQLND)
		case MYSQL_SERVER_PUBLIC_KEY:
#endif
			return IS_STRING;

		default:
			return IS_NULL;
	}
}