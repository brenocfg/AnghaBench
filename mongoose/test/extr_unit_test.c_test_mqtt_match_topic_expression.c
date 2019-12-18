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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  mg_mk_str (char*) ; 
 int mg_mqtt_vmatch_topic_expression (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *test_mqtt_match_topic_expression(void) {
  ASSERT(mg_mqtt_vmatch_topic_expression("foo", mg_mk_str("foo")));
  ASSERT(mg_mqtt_vmatch_topic_expression("/foo", mg_mk_str("/foo")));
  ASSERT(mg_mqtt_vmatch_topic_expression("+/foo", mg_mk_str("/foo")));
  ASSERT(!mg_mqtt_vmatch_topic_expression("foo", mg_mk_str("foobar")));
  ASSERT(mg_mqtt_vmatch_topic_expression("foo", mg_mk_str("foo/")));
  ASSERT(mg_mqtt_vmatch_topic_expression("foo", mg_mk_str("foo//")));
  ASSERT(!mg_mqtt_vmatch_topic_expression("foo", mg_mk_str("foo/bar")));
  ASSERT(!mg_mqtt_vmatch_topic_expression("foo", mg_mk_str("foo/+")));
  ASSERT(mg_mqtt_vmatch_topic_expression("foo/bar", mg_mk_str("foo/bar")));
  ASSERT(mg_mqtt_vmatch_topic_expression("foo/+", mg_mk_str("foo/bar")));
  ASSERT(mg_mqtt_vmatch_topic_expression("+/bar", mg_mk_str("foo/bar")));
  ASSERT(mg_mqtt_vmatch_topic_expression("+/+", mg_mk_str("foo/bar")));
  ASSERT(mg_mqtt_vmatch_topic_expression("foo/+/bar", mg_mk_str("foo//bar")));
  ASSERT(!mg_mqtt_vmatch_topic_expression("foo/+/+", mg_mk_str("foo/bar")));
  ASSERT(mg_mqtt_vmatch_topic_expression("foo/+/#", mg_mk_str("foo/bar")));
  ASSERT(mg_mqtt_vmatch_topic_expression("+/foo/bar", mg_mk_str("/foo/bar")));

  ASSERT(!mg_mqtt_vmatch_topic_expression("", mg_mk_str("")));
  ASSERT(mg_mqtt_vmatch_topic_expression("/", mg_mk_str("")));
  ASSERT(mg_mqtt_vmatch_topic_expression("/", mg_mk_str("/")));

  ASSERT(mg_mqtt_vmatch_topic_expression("#", mg_mk_str("")));
  ASSERT(mg_mqtt_vmatch_topic_expression("#", mg_mk_str("foo")));
  ASSERT(mg_mqtt_vmatch_topic_expression("#", mg_mk_str("foo/bar")));
  ASSERT(mg_mqtt_vmatch_topic_expression("foo/#", mg_mk_str("foo")));
  ASSERT(mg_mqtt_vmatch_topic_expression("foo/#", mg_mk_str("foo/")));
  ASSERT(mg_mqtt_vmatch_topic_expression("foo/#", mg_mk_str("foo/bar")));
  ASSERT(mg_mqtt_vmatch_topic_expression("foo/#", mg_mk_str("foo/bar/baz")));
  ASSERT(!mg_mqtt_vmatch_topic_expression("#/foo", mg_mk_str("foo")));
  ASSERT(!mg_mqtt_vmatch_topic_expression("#/foo", mg_mk_str("bar/foo")));

  return NULL;
}