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
struct mg_connection {int /*<<< orphan*/ * user_data; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_F_CLOSE_IMMEDIATELY ; 
 int /*<<< orphan*/  printf (char*,struct mg_connection*) ; 

__attribute__((used)) static void unproxy(struct mg_connection *c) {
  struct mg_connection *pc = (struct mg_connection *) c->user_data;
  if (pc != NULL) {
    pc->flags |= MG_F_CLOSE_IMMEDIATELY;
    pc->user_data = NULL;
    c->user_data = NULL;
  }
  printf("Closing connection %p\n", c);
}