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

/* Variables and functions */

int mg_null_if_udp_recv(struct mg_connection *c, void *buf, size_t len,
                        union socket_address *sa, size_t *sa_len) {
  (void) c;
  (void) buf;
  (void) len;
  (void) sa;
  (void) sa_len;
  return -1;
}