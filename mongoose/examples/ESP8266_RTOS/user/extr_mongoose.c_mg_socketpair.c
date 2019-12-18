#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
union socket_address {int /*<<< orphan*/  sa; TYPE_2__ sin; } ;
typedef  int socklen_t ;
typedef  scalar_t__ sock_t ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ INVALID_SOCKET ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 scalar_t__ bind (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ connect (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ getsockname (scalar_t__,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 scalar_t__ listen (scalar_t__,int) ; 
 int /*<<< orphan*/  memset (union socket_address*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_set_close_on_exec (scalar_t__) ; 
 scalar_t__ mg_socketpair_accept (scalar_t__,union socket_address*,int) ; 
 int /*<<< orphan*/  mg_socketpair_close (scalar_t__*) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int mg_socketpair(sock_t sp[2], int sock_type) {
  union socket_address sa, sa2;
  sock_t sock;
  socklen_t len = sizeof(sa.sin);
  int ret = 0;

  sock = sp[0] = sp[1] = INVALID_SOCKET;

  (void) memset(&sa, 0, sizeof(sa));
  sa.sin.sin_family = AF_INET;
  sa.sin.sin_addr.s_addr = htonl(0x7f000001); /* 127.0.0.1 */
  sa2 = sa;

  if ((sock = socket(AF_INET, sock_type, 0)) == INVALID_SOCKET) {
  } else if (bind(sock, &sa.sa, len) != 0) {
  } else if (sock_type == SOCK_STREAM && listen(sock, 1) != 0) {
  } else if (getsockname(sock, &sa.sa, &len) != 0) {
  } else if ((sp[0] = socket(AF_INET, sock_type, 0)) == INVALID_SOCKET) {
  } else if (sock_type == SOCK_STREAM && connect(sp[0], &sa.sa, len) != 0) {
  } else if (sock_type == SOCK_DGRAM &&
             (bind(sp[0], &sa2.sa, len) != 0 ||
              getsockname(sp[0], &sa2.sa, &len) != 0 ||
              connect(sp[0], &sa.sa, len) != 0 ||
              connect(sock, &sa2.sa, len) != 0)) {
  } else if ((sp[1] = (sock_type == SOCK_DGRAM ? sock : mg_socketpair_accept(
                                                            sock, &sa, len))) ==
             INVALID_SOCKET) {
  } else {
    mg_set_close_on_exec(sp[0]);
    mg_set_close_on_exec(sp[1]);
    if (sock_type == SOCK_STREAM) mg_socketpair_close(&sock);
    ret = 1;
  }

  if (!ret) {
    if (sp[0] != INVALID_SOCKET) mg_socketpair_close(&sp[0]);
    if (sp[1] != INVALID_SOCKET) mg_socketpair_close(&sp[1]);
    if (sock != INVALID_SOCKET) mg_socketpair_close(&sock);
  }

  return ret;
}