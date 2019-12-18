#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct hostent {scalar_t__ h_addrtype; int /*<<< orphan*/  h_length; int /*<<< orphan*/ * h_addr_list; } ;
typedef  int /*<<< orphan*/  php_socket ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ MAXFQDNLEN ; 
 int /*<<< orphan*/  PHP_SOCKET_ERROR (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ h_errno ; 
 scalar_t__ inet_aton (char*,struct in_addr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct hostent* php_network_gethostbyname (char*) ; 
 scalar_t__ strlen (char*) ; 

int php_set_inet_addr(struct sockaddr_in *sin, char *string, php_socket *php_sock) /* {{{ */
{
	struct in_addr tmp;
	struct hostent *host_entry;

	if (inet_aton(string, &tmp)) {
		sin->sin_addr.s_addr = tmp.s_addr;
	} else {
		if (strlen(string) > MAXFQDNLEN || ! (host_entry = php_network_gethostbyname(string))) {
			/* Note: < -10000 indicates a host lookup error */
#ifdef PHP_WIN32
			PHP_SOCKET_ERROR(php_sock, "Host lookup failed", WSAGetLastError());
#else
			PHP_SOCKET_ERROR(php_sock, "Host lookup failed", (-10000 - h_errno));
#endif
			return 0;
		}
		if (host_entry->h_addrtype != AF_INET) {
			php_error_docref(NULL, E_WARNING, "Host lookup failed: Non AF_INET domain returned on AF_INET socket");
			return 0;
		}
		memcpy(&(sin->sin_addr.s_addr), host_entry->h_addr_list[0], host_entry->h_length);
	}

	return 1;
}