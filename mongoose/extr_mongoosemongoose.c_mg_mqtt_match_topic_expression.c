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
struct mg_str {scalar_t__ len; } ;

/* Variables and functions */
 struct mg_str mg_mqtt_next_topic_component (struct mg_str*) ; 
 scalar_t__ mg_strcmp (struct mg_str,struct mg_str) ; 
 scalar_t__ mg_vcmp (struct mg_str*,char*) ; 

int mg_mqtt_match_topic_expression(struct mg_str exp, struct mg_str topic) {
  struct mg_str ec, tc;
  if (exp.len == 0) return 0;
  while (1) {
    ec = mg_mqtt_next_topic_component(&exp);
    tc = mg_mqtt_next_topic_component(&topic);
    if (ec.len == 0) {
      if (tc.len != 0) return 0;
      if (exp.len == 0) break;
      continue;
    }
    if (mg_vcmp(&ec, "+") == 0) {
      if (tc.len == 0 && topic.len == 0) return 0;
      continue;
    }
    if (mg_vcmp(&ec, "#") == 0) {
      /* Must be the last component in the expression or it's invalid. */
      return (exp.len == 0);
    }
    if (mg_strcmp(ec, tc) != 0) {
      return 0;
    }
  }
  return (tc.len == 0 && topic.len == 0);
}