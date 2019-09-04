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
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  init_test_connection (struct mg_connection*) ; 

__attribute__((used)) static struct mg_connection *create_test_connection() {
  struct mg_connection *nc = (struct mg_connection *) calloc(1, sizeof(*nc));
  init_test_connection(nc);
  return nc;
}