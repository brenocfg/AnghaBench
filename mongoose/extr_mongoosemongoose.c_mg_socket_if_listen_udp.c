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
typedef  union socket_address {int dummy; } socket_address ;
struct mg_connection {int dummy; } ;
typedef  scalar_t__ sock_t ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int mg_get_errno () ; 
 scalar_t__ mg_open_listening_socket (union socket_address*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_sock_set (struct mg_connection*,scalar_t__) ; 

__attribute__((used)) static int mg_socket_if_listen_udp(struct mg_connection *nc,
                                   union socket_address *sa) {
  sock_t sock = mg_open_listening_socket(sa, SOCK_DGRAM, 0);
  if (sock == INVALID_SOCKET) return (mg_get_errno() ? mg_get_errno() : 1);
  mg_sock_set(nc, sock);
  return 0;
}