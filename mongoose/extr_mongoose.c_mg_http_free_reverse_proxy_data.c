#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mg_reverse_proxy_data {int /*<<< orphan*/ * linked_conn; } ;
struct TYPE_4__ {TYPE_1__* linked_conn; } ;
struct mg_http_proto_data {TYPE_2__ reverse_proxy_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 struct mg_http_proto_data* mg_http_get_proto_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mg_http_free_reverse_proxy_data(struct mg_reverse_proxy_data *rpd) {
  if (rpd->linked_conn != NULL) {
    /*
     * Connection has linked one, we have to unlink & close it
     * since _this_ connection is going to die and
     * it doesn't make sense to keep another one
     */
    struct mg_http_proto_data *pd = mg_http_get_proto_data(rpd->linked_conn);
    if (pd->reverse_proxy_data.linked_conn != NULL) {
      pd->reverse_proxy_data.linked_conn->flags |= MG_F_SEND_AND_CLOSE;
      pd->reverse_proxy_data.linked_conn = NULL;
    }
    rpd->linked_conn = NULL;
  }
}