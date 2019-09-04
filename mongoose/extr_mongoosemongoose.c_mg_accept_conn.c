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
struct TYPE_2__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
union socket_address {TYPE_1__ sin; int /*<<< orphan*/  sa; } ;
struct mg_connection {int /*<<< orphan*/  sock; } ;
typedef  int socklen_t ;
typedef  scalar_t__ sock_t ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ INVALID_SOCKET ; 
 scalar_t__ accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_get_errno () ; 
 struct mg_connection* mg_if_accept_new_conn (struct mg_connection*) ; 
 int /*<<< orphan*/  mg_if_accept_tcp_cb (struct mg_connection*,union socket_address*,int) ; 
 scalar_t__ mg_is_error () ; 
 int /*<<< orphan*/  mg_sock_set (struct mg_connection*,scalar_t__) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mg_accept_conn(struct mg_connection *lc) {
  struct mg_connection *nc;
  union socket_address sa;
  socklen_t sa_len = sizeof(sa);
  /* NOTE(lsm): on Windows, sock is always > FD_SETSIZE */
  sock_t sock = accept(lc->sock, &sa.sa, &sa_len);
  if (sock == INVALID_SOCKET) {
    if (mg_is_error()) {
      DBG(("%p: failed to accept: %d", lc, mg_get_errno()));
    }
    return 0;
  }
  nc = mg_if_accept_new_conn(lc);
  if (nc == NULL) {
    closesocket(sock);
    return 0;
  }
  DBG(("%p conn from %s:%d", nc, inet_ntoa(sa.sin.sin_addr),
       ntohs(sa.sin.sin_port)));
  mg_sock_set(nc, sock);
  mg_if_accept_tcp_cb(nc, &sa, sa_len);
  return 1;
}