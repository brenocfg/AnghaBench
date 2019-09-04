#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {int not_found; int valid; int /*<<< orphan*/  data; scalar_t__ no_cacheable; int /*<<< orphan*/  len; } ;
typedef  TYPE_5__ ngx_http_variable_value_t ;
struct TYPE_14__ {TYPE_4__* request_body; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_12__ {TYPE_3__* temp_file; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_10__ {TYPE_1__ name; } ;
struct TYPE_11__ {TYPE_2__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_variable_request_body_file(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    if (r->request_body == NULL || r->request_body->temp_file == NULL) {
        v->not_found = 1;

        return NGX_OK;
    }

    v->len = r->request_body->temp_file->file.name.len;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->data = r->request_body->temp_file->file.name.data;

    return NGX_OK;
}