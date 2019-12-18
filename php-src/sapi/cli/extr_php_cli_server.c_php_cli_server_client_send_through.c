#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ php_cli_server_client ;

/* Variables and functions */
 int /*<<< orphan*/  POLLOUT ; 
 int SOCK_EAGAIN ; 
 int /*<<< orphan*/  php_handle_aborted_connection () ; 
 int php_pollfd_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 
 int php_socket_errno () ; 
 scalar_t__ send (int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t php_cli_server_client_send_through(php_cli_server_client *client, const char *str, size_t str_len) /* {{{ */
{
	struct timeval tv = { 10, 0 };
#ifdef PHP_WIN32
	int nbytes_left = (int)str_len;
#else
	ssize_t nbytes_left = (ssize_t)str_len;
#endif
	do {
#ifdef PHP_WIN32
		int nbytes_sent;
#else
		ssize_t nbytes_sent;
#endif

		nbytes_sent = send(client->sock, str + str_len - nbytes_left, nbytes_left, 0);
		if (nbytes_sent < 0) {
			int err = php_socket_errno();
			if (err == SOCK_EAGAIN) {
				int nfds = php_pollfd_for(client->sock, POLLOUT, &tv);
				if (nfds > 0) {
					continue;
				} else if (nfds < 0) {
					/* error */
					php_handle_aborted_connection();
					return nbytes_left;
				} else {
					/* timeout */
					php_handle_aborted_connection();
					return nbytes_left;
				}
			} else {
				php_handle_aborted_connection();
				return nbytes_left;
			}
		}
		nbytes_left -= nbytes_sent;
	} while (nbytes_left > 0);

	return str_len;
}