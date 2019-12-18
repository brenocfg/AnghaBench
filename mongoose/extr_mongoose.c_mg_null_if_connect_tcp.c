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
struct mg_connection {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_F_CLOSE_IMMEDIATELY ; 

__attribute__((used)) static void mg_null_if_connect_tcp(struct mg_connection *c,
                                   const union socket_address *sa) {
  c->flags |= MG_F_CLOSE_IMMEDIATELY;
  (void) sa;
}