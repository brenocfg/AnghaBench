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
struct mg_mgr {struct mg_connection* active_connections; } ;
struct mg_connection {struct mg_connection* next; } ;

/* Variables and functions */

struct mg_connection *mg_next(struct mg_mgr *s, struct mg_connection *conn) {
  return conn == NULL ? s->active_connections : conn->next;
}