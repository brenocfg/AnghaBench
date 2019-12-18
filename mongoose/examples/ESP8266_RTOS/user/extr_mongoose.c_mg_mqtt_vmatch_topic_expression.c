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
struct mg_str {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mg_mk_str (char const*) ; 
 int mg_mqtt_match_topic_expression (int /*<<< orphan*/ ,struct mg_str) ; 

int mg_mqtt_vmatch_topic_expression(const char *exp, struct mg_str topic) {
  return mg_mqtt_match_topic_expression(mg_mk_str(exp), topic);
}