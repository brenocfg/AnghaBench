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
struct sockaddr_in6 {int sin6_family; void* sin6_port; } ;
struct sockaddr_in {int sin_family; void* sin_port; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  sockoptval ;
typedef  int socklen_t ;
typedef  int php_socket_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int SOCK_CONN_ERR ; 
 int SOCK_ERR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 long STREAM_SOCKOP_IPV6_V6ONLY ; 
 long STREAM_SOCKOP_IPV6_V6ONLY_ENABLED ; 
 long STREAM_SOCKOP_SO_BROADCAST ; 
 long STREAM_SOCKOP_SO_REUSEPORT ; 
 long STREAM_SOCKOP_TCP_NODELAY ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 void* htons (unsigned int) ; 
 int /*<<< orphan*/  php_network_freeaddresses (struct sockaddr**) ; 
 int php_network_getaddresses (char const*,int,struct sockaddr***,int /*<<< orphan*/ **) ; 
 int php_socket_errno () ; 
 int /*<<< orphan*/ * php_socket_error_str (int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 

php_socket_t php_network_bind_socket_to_local_addr(const char *host, unsigned port,
		int socktype, long sockopts, zend_string **error_string, int *error_code
		)
{
	int num_addrs, n, err = 0;
	php_socket_t sock;
	struct sockaddr **sal, **psal, *sa;
	socklen_t socklen;
	int sockoptval = 1;

	num_addrs = php_network_getaddresses(host, socktype, &psal, error_string);

	if (num_addrs == 0) {
		/* could not resolve address(es) */
		return -1;
	}

	for (sal = psal; *sal != NULL; sal++) {
		sa = *sal;

		/* create a socket for this address */
		sock = socket(sa->sa_family, socktype, 0);

		if (sock == SOCK_ERR) {
			continue;
		}

		switch (sa->sa_family) {
#if HAVE_GETADDRINFO && HAVE_IPV6
			case AF_INET6:
				((struct sockaddr_in6 *)sa)->sin6_family = sa->sa_family;
				((struct sockaddr_in6 *)sa)->sin6_port = htons(port);
				socklen = sizeof(struct sockaddr_in6);
				break;
#endif
			case AF_INET:
				((struct sockaddr_in *)sa)->sin_family = sa->sa_family;
				((struct sockaddr_in *)sa)->sin_port = htons(port);
				socklen = sizeof(struct sockaddr_in);
				break;
			default:
				/* Unknown family */
				socklen = 0;
				sa = NULL;
		}

		if (sa) {
			/* attempt to bind */

#ifdef SO_REUSEADDR
			setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&sockoptval, sizeof(sockoptval));
#endif
#ifdef IPV6_V6ONLY
			if (sockopts & STREAM_SOCKOP_IPV6_V6ONLY) {
				int ipv6_val = !!(sockopts & STREAM_SOCKOP_IPV6_V6ONLY_ENABLED);
				setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (char*)&ipv6_val, sizeof(sockoptval));
			}
#endif
#ifdef SO_REUSEPORT
			if (sockopts & STREAM_SOCKOP_SO_REUSEPORT) {
				setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (char*)&sockoptval, sizeof(sockoptval));
			}
#endif
#ifdef SO_BROADCAST
			if (sockopts & STREAM_SOCKOP_SO_BROADCAST) {
				setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&sockoptval, sizeof(sockoptval));
			}
#endif
#ifdef TCP_NODELAY
			if (sockopts & STREAM_SOCKOP_TCP_NODELAY) {
				setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&sockoptval, sizeof(sockoptval));
			}
#endif

			n = bind(sock, sa, socklen);

			if (n != SOCK_CONN_ERR) {
				goto bound;
			}

			err = php_socket_errno();
		}

		closesocket(sock);
	}
	sock = -1;

	if (error_code) {
		*error_code = err;
	}
	if (error_string) {
		*error_string = php_socket_error_str(err);
	}

bound:

	php_network_freeaddresses(psal);

	return sock;

}