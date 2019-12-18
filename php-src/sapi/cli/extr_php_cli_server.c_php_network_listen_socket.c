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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  val ;
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
struct sockaddr {int sa_family; } ;
typedef  int socklen_t ;
typedef  int php_socket_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ SOCK_CONN_ERR ; 
 int SOCK_EADDRINUSE ; 
 int SOCK_EINVAL ; 
 int SOCK_ERR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 scalar_t__ ZEND_VALID_SOCKET (int) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 void* htons (int) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 int ntohs (void*) ; 
 int /*<<< orphan*/  pefree (struct sockaddr*,int) ; 
 struct sockaddr* pemalloc (int,int) ; 
 int php_cli_server_workers_max ; 
 int /*<<< orphan*/  php_network_freeaddresses (struct sockaddr**) ; 
 int php_network_getaddresses (char const*,int,struct sockaddr***,int /*<<< orphan*/ **) ; 
 int php_socket_errno () ; 
 int /*<<< orphan*/ * php_socket_error_str (int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static php_socket_t php_network_listen_socket(const char *host, int *port, int socktype, int *af, socklen_t *socklen, zend_string **errstr) /* {{{ */
{
	php_socket_t retval = SOCK_ERR;
	int err = 0;
	struct sockaddr *sa = NULL, **p, **sal;

	int num_addrs = php_network_getaddresses(host, socktype, &sal, errstr);
	if (num_addrs == 0) {
		return -1;
	}
	for (p = sal; *p; p++) {
		if (sa) {
			pefree(sa, 1);
			sa = NULL;
		}

		retval = socket((*p)->sa_family, socktype, 0);
		if (retval == SOCK_ERR) {
			continue;
		}

		switch ((*p)->sa_family) {
#if HAVE_GETADDRINFO && HAVE_IPV6
		case AF_INET6:
			sa = pemalloc(sizeof(struct sockaddr_in6), 1);
			*(struct sockaddr_in6 *)sa = *(struct sockaddr_in6 *)*p;
			((struct sockaddr_in6 *)sa)->sin6_port = htons(*port);
			*socklen = sizeof(struct sockaddr_in6);
			break;
#endif
		case AF_INET:
			sa = pemalloc(sizeof(struct sockaddr_in), 1);
			*(struct sockaddr_in *)sa = *(struct sockaddr_in *)*p;
			((struct sockaddr_in *)sa)->sin_port = htons(*port);
			*socklen = sizeof(struct sockaddr_in);
			break;
		default:
			/* Unknown family */
			*socklen = 0;
			closesocket(retval);
			continue;
		}

#ifdef SO_REUSEADDR
		{
			int val = 1;
			setsockopt(retval, SOL_SOCKET, SO_REUSEADDR, (char*)&val, sizeof(val));
		}
#endif

#if defined(HAVE_FORK) && defined(SO_REUSEPORT)
		if (php_cli_server_workers_max > 1) {
			int val = 1;
			setsockopt(retval, SOL_SOCKET, SO_REUSEPORT, (char*)&val, sizeof(val));
		}
#endif

		if (bind(retval, sa, *socklen) == SOCK_CONN_ERR) {
			err = php_socket_errno();
			if (err == SOCK_EINVAL || err == SOCK_EADDRINUSE) {
				goto out;
			}
			closesocket(retval);
			retval = SOCK_ERR;
			continue;
		}
		err = 0;

		*af = sa->sa_family;
		if (*port == 0) {
			if (getsockname(retval, sa, socklen)) {
				err = php_socket_errno();
				goto out;
			}
			switch (sa->sa_family) {
#if HAVE_GETADDRINFO && HAVE_IPV6
			case AF_INET6:
				*port = ntohs(((struct sockaddr_in6 *)sa)->sin6_port);
				break;
#endif
			case AF_INET:
				*port = ntohs(((struct sockaddr_in *)sa)->sin_port);
				break;
			}
		}

		break;
	}

	if (retval == SOCK_ERR) {
		goto out;
	}

	if (listen(retval, SOMAXCONN)) {
		err = php_socket_errno();
		goto out;
	}

out:
	if (sa) {
		pefree(sa, 1);
	}
	if (sal) {
		php_network_freeaddresses(sal);
	}
	if (err) {
		if (ZEND_VALID_SOCKET(retval)) {
			closesocket(retval);
		}
		if (errstr) {
			*errstr = php_socket_error_str(err);
		}
		return SOCK_ERR;
	}
	return retval;
}