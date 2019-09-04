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
struct fpm_worker_pool_s {TYPE_1__* config; } ;
struct TYPE_2__ {int /*<<< orphan*/  listen_address; } ;

/* Variables and functions */
 int ZLOG_ALERT ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  ZLOG_NOTICE ; 
 int atoi (char*) ; 
 int fpm_socket_af_inet_socket_by_addr (struct fpm_worker_pool_s*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int strspn (char*,char*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 
 int zlog_set_level (int) ; 

__attribute__((used)) static int fpm_socket_af_inet_listening_socket(struct fpm_worker_pool_s *wp) /* {{{ */
{
	char *dup_address = strdup(wp->config->listen_address);
	char *port_str = strrchr(dup_address, ':');
	char *addr = NULL;
	int addr_len;
	int port = 0;
	int sock = -1;

	if (port_str) { /* this is host:port pair */
		*port_str++ = '\0';
		port = atoi(port_str);
		addr = dup_address;

		/* strip brackets from address for getaddrinfo */
		addr_len = strlen(addr);
		if (addr[0] == '[' && addr[addr_len - 1] == ']') {
			addr[addr_len - 1] = '\0';
			addr++;
		}

	} else if (strlen(dup_address) == strspn(dup_address, "0123456789")) { /* this is port */
		port = atoi(dup_address);
		port_str = dup_address;
	}

	if (port == 0) {
		zlog(ZLOG_ERROR, "invalid port value '%s'", port_str);
		return -1;
	}

	if (addr) {
		/* Bind a specific address */
		sock = fpm_socket_af_inet_socket_by_addr(wp, addr, port_str);
	} else {
		/* Bind ANYADDR
		 *
		 * Try "::" first as that covers IPv6 ANYADDR and mapped IPv4 ANYADDR
		 * silencing warnings since failure is an option
		 *
		 * If that fails (because AF_INET6 is unsupported) retry with 0.0.0.0
		 */
		int old_level = zlog_set_level(ZLOG_ALERT);
		sock = fpm_socket_af_inet_socket_by_addr(wp, "::", port_str);
		zlog_set_level(old_level);

		if (sock < 0) {
			zlog(ZLOG_NOTICE, "Failed implicitly binding to ::, retrying with 0.0.0.0");
			sock = fpm_socket_af_inet_socket_by_addr(wp, "0.0.0.0", port_str);
		}
	}

	free(dup_address);

	return sock;
}