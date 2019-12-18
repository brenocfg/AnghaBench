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
struct mg_connection {struct mg_connection* user_data; } ;

/* Variables and functions */

__attribute__((used)) static void link_conns(struct mg_connection *nc1, struct mg_connection *nc2) {
  nc1->user_data = nc2;
  nc2->user_data = nc1;
}