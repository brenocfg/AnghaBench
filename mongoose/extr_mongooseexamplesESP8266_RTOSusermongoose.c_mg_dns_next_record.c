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
struct mg_dns_resource_record {int rtype; } ;
struct mg_dns_message {int num_answers; struct mg_dns_resource_record* answers; } ;

/* Variables and functions */

struct mg_dns_resource_record *mg_dns_next_record(
    struct mg_dns_message *msg, int query,
    struct mg_dns_resource_record *prev) {
  struct mg_dns_resource_record *rr;

  for (rr = (prev == NULL ? msg->answers : prev + 1);
       rr - msg->answers < msg->num_answers; rr++) {
    if (rr->rtype == query) {
      return rr;
    }
  }
  return NULL;
}