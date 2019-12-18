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
struct mg_connection {int /*<<< orphan*/ * user_data; } ;

/* Variables and functions */

__attribute__((used)) static void unlink_conns(struct mg_connection *nc1) {
  struct mg_connection *nc2 = (struct mg_connection *) nc1->user_data;
  if (nc1->user_data != NULL) {
    nc1->user_data = NULL;
    nc2->user_data = NULL;
  }
}