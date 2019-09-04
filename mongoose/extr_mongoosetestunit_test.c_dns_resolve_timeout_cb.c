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
struct mg_dns_message {int dummy; } ;
typedef  enum mg_resolve_err { ____Placeholder_mg_resolve_err } mg_resolve_err ;

/* Variables and functions */

__attribute__((used)) static void dns_resolve_timeout_cb(struct mg_dns_message *msg, void *data,
                                   enum mg_resolve_err e) {
  (void) e;
  if (msg == NULL) {
    *(int *) data = 1;
  }
}