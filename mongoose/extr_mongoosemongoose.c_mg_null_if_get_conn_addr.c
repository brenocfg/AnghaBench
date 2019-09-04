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

__attribute__((used)) static void mg_null_if_get_conn_addr(struct mg_connection *c, int remote,
                                     union socket_address *sa) {
  (void) c;
  (void) remote;
  (void) sa;
}