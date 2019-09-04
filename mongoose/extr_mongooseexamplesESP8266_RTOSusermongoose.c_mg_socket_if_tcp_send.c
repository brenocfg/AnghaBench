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
struct mg_connection {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 scalar_t__ MG_SEND_FUNC (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_is_error () ; 

__attribute__((used)) static int mg_socket_if_tcp_send(struct mg_connection *nc, const void *buf,
                                 size_t len) {
  int n = (int) MG_SEND_FUNC(nc->sock, buf, len, 0);
  if (n < 0 && !mg_is_error()) n = 0;
  return n;
}