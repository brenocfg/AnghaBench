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
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mg_destroy_conn (struct mg_connection*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_test_connection(struct mg_connection *nc) {
  mg_destroy_conn(nc, 0 /* destroy_if */);
}