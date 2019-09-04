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
typedef  int /*<<< orphan*/  working_timeout ;
struct timeval {int dummy; } ;
struct sockaddr_in {int sin_family; int /*<<< orphan*/  sin_zero; int /*<<< orphan*/  sin_addr; void* sin_port; } ;
struct sockaddr {int sa_family; } ;
typedef  int socklen_t ;
typedef  int php_socket_t ;

/* Variables and functions */
#define  AF_INET 128 
 int /*<<< orphan*/  E_WARNING ; 
 int PHP_TIMEOUT_ERROR_VALUE ; 
 int SOCK_ERR ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  efree (struct sockaddr*) ; 
 struct sockaddr_in* emalloc (int) ; 
 int /*<<< orphan*/  errno ; 
 void* htons (unsigned short) ; 
 int /*<<< orphan*/  inet_aton (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct timeval*,struct timeval*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,...) ; 
 int php_network_connect_socket (int,struct sockaddr*,int,int,struct timeval*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  php_network_freeaddresses (struct sockaddr**) ; 
 int php_network_getaddresses (char const*,int,struct sockaddr***,int /*<<< orphan*/ **) ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

php_socket_t php_network_connect_socket_to_host(const char *host, unsigned short port,
		int socktype, int asynchronous, struct timeval *timeout, zend_string **error_string,
		int *error_code, char *bindto, unsigned short bindport, long sockopts
		)
{
	int num_addrs, n, fatal = 0;
	php_socket_t sock;
	struct sockaddr **sal, **psal, *sa;
	struct timeval working_timeout;
	socklen_t socklen;
#if HAVE_GETTIMEOFDAY
	struct timeval limit_time, time_now;
#endif

	num_addrs = php_network_getaddresses(host, socktype, &psal, error_string);

	if (num_addrs == 0) {
		/* could not resolve address(es) */
		return -1;
	}

	if (timeout) {
		memcpy(&working_timeout, timeout, sizeof(working_timeout));
#if HAVE_GETTIMEOFDAY
		gettimeofday(&limit_time, NULL);
		limit_time.tv_sec += working_timeout.tv_sec;
		limit_time.tv_usec += working_timeout.tv_usec;
		if (limit_time.tv_usec >= 1000000) {
			limit_time.tv_usec -= 1000000;
			limit_time.tv_sec++;
		}
#endif
	}

	for (sal = psal; !fatal && *sal != NULL; sal++) {
		sa = *sal;

		/* create a socket for this address */
		sock = socket(sa->sa_family, socktype, 0);

		if (sock == SOCK_ERR) {
			continue;
		}

		switch (sa->sa_family) {
#if HAVE_GETADDRINFO && HAVE_IPV6
			case AF_INET6:
				if (!bindto || strchr(bindto, ':')) {
					((struct sockaddr_in6 *)sa)->sin6_family = sa->sa_family;
					((struct sockaddr_in6 *)sa)->sin6_port = htons(port);
					socklen = sizeof(struct sockaddr_in6);
				} else {
					socklen = 0;
					sa = NULL;
				}
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
			/* make a connection attempt */

			if (bindto) {
				struct sockaddr *local_address = NULL;
				int local_address_len = 0;

				if (sa->sa_family == AF_INET) {
					if (strchr(bindto,':')) {
						goto skip_bind;
					}
					struct sockaddr_in *in4 = emalloc(sizeof(struct sockaddr_in));

					local_address = (struct sockaddr*)in4;
					local_address_len = sizeof(struct sockaddr_in);

					in4->sin_family = sa->sa_family;
					in4->sin_port = htons(bindport);
					if (!inet_aton(bindto, &in4->sin_addr)) {
						php_error_docref(NULL, E_WARNING, "Invalid IP Address: %s", bindto);
						goto skip_bind;
					}
					memset(&(in4->sin_zero), 0, sizeof(in4->sin_zero));
				}
#if HAVE_IPV6 && HAVE_INET_PTON
				 else { /* IPV6 */
					struct sockaddr_in6 *in6 = emalloc(sizeof(struct sockaddr_in6));

					local_address = (struct sockaddr*)in6;
					local_address_len = sizeof(struct sockaddr_in6);

					in6->sin6_family = sa->sa_family;
					in6->sin6_port = htons(bindport);
					if (inet_pton(AF_INET6, bindto, &in6->sin6_addr) < 1) {
						php_error_docref(NULL, E_WARNING, "Invalid IP Address: %s", bindto);
						goto skip_bind;
					}
				}
#endif

				if (!local_address || bind(sock, local_address, local_address_len)) {
					php_error_docref(NULL, E_WARNING, "failed to bind to '%s:%d', system said: %s", bindto, bindport, strerror(errno));
				}
skip_bind:
				if (local_address) {
					efree(local_address);
				}
			}
			/* free error string received during previous iteration (if any) */
			if (error_string && *error_string) {
				zend_string_release_ex(*error_string, 0);
				*error_string = NULL;
			}

#ifdef SO_BROADCAST
			{
				int val = 1;
				if (sockopts & STREAM_SOCKOP_SO_BROADCAST) {
					setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&val, sizeof(val));
				}
			}
#endif

#ifdef TCP_NODELAY
			{
				int val = 1;
				if (sockopts & STREAM_SOCKOP_TCP_NODELAY) {
					setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&val, sizeof(val));
				}
			}
#endif
			n = php_network_connect_socket(sock, sa, socklen, asynchronous,
					timeout ? &working_timeout : NULL,
					error_string, error_code);

			if (n != -1) {
				goto connected;
			}

			/* adjust timeout for next attempt */
#if HAVE_GETTIMEOFDAY
			if (timeout) {
				gettimeofday(&time_now, NULL);

				if (timercmp(&time_now, &limit_time, >=)) {
					/* time limit expired; don't attempt any further connections */
					fatal = 1;
				} else {
					/* work out remaining time */
					sub_times(limit_time, time_now, &working_timeout);
				}
			}
#else
			if (error_code && *error_code == PHP_TIMEOUT_ERROR_VALUE) {
				/* Don't even bother trying to connect to the next alternative;
				 * we have no way to determine how long we have already taken
				 * and it is quite likely that the next attempt will fail too. */
				fatal = 1;
			} else {
				/* re-use the same initial timeout.
				 * Not the best thing, but in practice it should be good-enough */
				if (timeout) {
					memcpy(&working_timeout, timeout, sizeof(working_timeout));
				}
			}
#endif
		}

		closesocket(sock);
	}
	sock = -1;

connected:

	php_network_freeaddresses(psal);

	return sock;
}