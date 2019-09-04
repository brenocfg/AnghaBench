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
struct sockaddr {int dummy; } ;
struct fpm_worker_pool_s {int /*<<< orphan*/  listen_address_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_GET_USE_SOCKET ; 
 int /*<<< orphan*/  FPM_STORE_USE_SOCKET ; 
 int fpm_sockets_hash_op (int,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fpm_sockets_new_listening_socket (struct fpm_worker_pool_s*,struct sockaddr*,int) ; 

__attribute__((used)) static int fpm_sockets_get_listening_socket(struct fpm_worker_pool_s *wp, struct sockaddr *sa, int socklen) /* {{{ */
{
	int sock;

	sock = fpm_sockets_hash_op(0, sa, 0, wp->listen_address_domain, FPM_GET_USE_SOCKET);
	if (sock >= 0) {
		return sock;
	}

	sock = fpm_sockets_new_listening_socket(wp, sa, socklen);
	fpm_sockets_hash_op(sock, sa, 0, wp->listen_address_domain, FPM_STORE_USE_SOCKET);

	return sock;
}