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
struct mg_http_proto_data {int dummy; } ;
struct mg_connection {scalar_t__ proto_data; } ;

/* Variables and functions */

__attribute__((used)) static struct mg_http_proto_data *mg_http_get_proto_data(
    struct mg_connection *c) {
  return (struct mg_http_proto_data *) c->proto_data;
}