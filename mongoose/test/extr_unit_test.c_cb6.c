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
struct mg_connection {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_F_USER_4 ; 
 int /*<<< orphan*/  MG_F_WANT_READ ; 

__attribute__((used)) static void cb6(struct mg_connection *nc, int ev, void *ev_data) {
  (void) ev;
  (void) ev_data;
  nc->flags |= MG_F_USER_4;
  nc->flags |= MG_F_WANT_READ; /* Should not be allowed. */
}