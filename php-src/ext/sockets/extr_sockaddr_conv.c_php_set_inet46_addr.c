#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct sockaddr_in6 {int /*<<< orphan*/  member_0; } ;
struct sockaddr_in {int /*<<< orphan*/  member_0; } ;
typedef  int socklen_t ;
struct TYPE_8__ {scalar_t__ type; } ;
typedef  TYPE_1__ php_socket ;
struct TYPE_9__ {scalar_t__ ss_family; } ;
typedef  TYPE_2__ php_sockaddr_storage ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ php_set_inet6_addr (struct sockaddr_in6*,char*,TYPE_1__*) ; 
 scalar_t__ php_set_inet_addr (struct sockaddr_in6*,char*,TYPE_1__*) ; 

int php_set_inet46_addr(php_sockaddr_storage *ss, socklen_t *ss_len, char *string, php_socket *php_sock) /* {{{ */
{
	if (php_sock->type == AF_INET) {
		struct sockaddr_in t = {0};
		if (php_set_inet_addr(&t, string, php_sock)) {
			memcpy(ss, &t, sizeof t);
			ss->ss_family = AF_INET;
			*ss_len = sizeof(t);
			return 1;
		}
	}
#if HAVE_IPV6
	else if (php_sock->type == AF_INET6) {
		struct sockaddr_in6 t = {0};
		if (php_set_inet6_addr(&t, string, php_sock)) {
			memcpy(ss, &t, sizeof t);
			ss->ss_family = AF_INET6;
			*ss_len = sizeof(t);
			return 1;
		}
	}
#endif
	else {
		php_error_docref(NULL, E_WARNING,
			"IP address used in the context of an unexpected type of socket");
	}
	return 0;
}