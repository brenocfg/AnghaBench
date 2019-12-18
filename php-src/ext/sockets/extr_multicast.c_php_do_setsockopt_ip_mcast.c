#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct in_addr {int dummy; } ;
typedef  int socklen_t ;
struct TYPE_6__ {int /*<<< orphan*/  bsd_socket; } ;
typedef  TYPE_1__ php_socket ;
typedef  int /*<<< orphan*/  ipv4_mcast_ttl_lback ;
typedef  int /*<<< orphan*/  if_addr ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
#define  IP_MULTICAST_IF 136 
#define  IP_MULTICAST_LOOP 135 
#define  IP_MULTICAST_TTL 134 
 int /*<<< orphan*/  IS_TRUE ; 
#define  PHP_MCAST_BLOCK_SOURCE 133 
#define  PHP_MCAST_JOIN_GROUP 132 
#define  PHP_MCAST_JOIN_SOURCE_GROUP 131 
#define  PHP_MCAST_LEAVE_GROUP 130 
#define  PHP_MCAST_LEAVE_SOURCE_GROUP 129 
#define  PHP_MCAST_UNBLOCK_SOURCE 128 
 int /*<<< orphan*/  PHP_SOCKET_ERROR (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 long Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_boolean_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_long_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int php_do_mcast_opt (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int php_get_if_index_from_zval (int /*<<< orphan*/ *,unsigned int*) ; 
 int php_if_index_to_addr4 (unsigned int,TYPE_1__*,struct in_addr*) ; 
 int setsockopt (int /*<<< orphan*/ ,int,int,void*,int) ; 

int php_do_setsockopt_ip_mcast(php_socket *php_sock,
							   int level,
							   int optname,
							   zval *arg4)
{
	unsigned int	if_index;
	struct in_addr	if_addr;
	void 			*opt_ptr;
	socklen_t		optlen;
	unsigned char	ipv4_mcast_ttl_lback;
	int				retval;

	switch (optname) {
	case PHP_MCAST_JOIN_GROUP:
	case PHP_MCAST_LEAVE_GROUP:
#ifdef HAS_MCAST_EXT
	case PHP_MCAST_BLOCK_SOURCE:
	case PHP_MCAST_UNBLOCK_SOURCE:
	case PHP_MCAST_JOIN_SOURCE_GROUP:
	case PHP_MCAST_LEAVE_SOURCE_GROUP:
#endif
		if (php_do_mcast_opt(php_sock, level, optname, arg4) == FAILURE) {
			return FAILURE;
		} else {
			return SUCCESS;
		}

	case IP_MULTICAST_IF:
		if (php_get_if_index_from_zval(arg4, &if_index) == FAILURE) {
			return FAILURE;
		}

		if (php_if_index_to_addr4(if_index, php_sock, &if_addr) == FAILURE) {
			return FAILURE;
		}
		opt_ptr = &if_addr;
		optlen	= sizeof(if_addr);
		goto dosockopt;

	case IP_MULTICAST_LOOP:
		convert_to_boolean_ex(arg4);
		ipv4_mcast_ttl_lback = (unsigned char) (Z_TYPE_P(arg4) == IS_TRUE);
		goto ipv4_loop_ttl;

	case IP_MULTICAST_TTL:
		convert_to_long_ex(arg4);
		if (Z_LVAL_P(arg4) < 0L || Z_LVAL_P(arg4) > 255L) {
			php_error_docref(NULL, E_WARNING,
					"Expected a value between 0 and 255");
			return FAILURE;
		}
		ipv4_mcast_ttl_lback = (unsigned char) Z_LVAL_P(arg4);
ipv4_loop_ttl:
		opt_ptr = &ipv4_mcast_ttl_lback;
		optlen	= sizeof(ipv4_mcast_ttl_lback);
		goto dosockopt;
	}

	return 1;

dosockopt:
	retval = setsockopt(php_sock->bsd_socket, level, optname, opt_ptr, optlen);
	if (retval != 0) {
		PHP_SOCKET_ERROR(php_sock, "unable to set socket option", errno);
		return FAILURE;
	}

	return SUCCESS;
}