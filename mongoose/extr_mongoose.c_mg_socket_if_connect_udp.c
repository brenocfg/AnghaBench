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
struct mg_connection {scalar_t__ sock; int err; int flags; } ;
typedef  int /*<<< orphan*/  optval ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ INVALID_SOCKET ; 
 int MG_F_ENABLE_BROADCAST ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int mg_get_errno () ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mg_socket_if_connect_udp(struct mg_connection *nc) {
  nc->sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (nc->sock == INVALID_SOCKET) {
    nc->err = mg_get_errno() ? mg_get_errno() : 1;
    return;
  }
  if (nc->flags & MG_F_ENABLE_BROADCAST) {
    int optval = 1;
    if (setsockopt(nc->sock, SOL_SOCKET, SO_BROADCAST, (const char *) &optval,
                   sizeof(optval)) < 0) {
      nc->err = mg_get_errno() ? mg_get_errno() : 1;
      return;
    }
  }
  nc->err = 0;
}