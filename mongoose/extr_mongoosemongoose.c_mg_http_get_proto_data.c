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
struct mg_connection {int /*<<< orphan*/ * proto_data; int /*<<< orphan*/  proto_data_destructor; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MG_CALLOC (int,int) ; 
 int /*<<< orphan*/  mg_http_conn_destructor ; 

__attribute__((used)) static struct mg_http_proto_data *mg_http_get_proto_data(
    struct mg_connection *c) {
  if (c->proto_data == NULL) {
    c->proto_data = MG_CALLOC(1, sizeof(struct mg_http_proto_data));
    c->proto_data_destructor = mg_http_conn_destructor;
  }

  return (struct mg_http_proto_data *) c->proto_data;
}