#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__ value; } ;
typedef  TYPE_2__ ngx_table_elt_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_12__ {size_t nelts; TYPE_2__** elts; } ;
typedef  TYPE_4__ ngx_array_t ;
typedef  int /*<<< orphan*/  ngx_addr_t ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_get_forwarded_addr_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int) ; 

ngx_int_t
ngx_http_get_forwarded_addr(ngx_http_request_t *r, ngx_addr_t *addr,
    ngx_array_t *headers, ngx_str_t *value, ngx_array_t *proxies,
    int recursive)
{
    ngx_int_t          rc;
    ngx_uint_t         i, found;
    ngx_table_elt_t  **h;

    if (headers == NULL) {
        return ngx_http_get_forwarded_addr_internal(r, addr, value->data,
                                                    value->len, proxies,
                                                    recursive);
    }

    i = headers->nelts;
    h = headers->elts;

    rc = NGX_DECLINED;

    found = 0;

    while (i-- > 0) {
        rc = ngx_http_get_forwarded_addr_internal(r, addr, h[i]->value.data,
                                                  h[i]->value.len, proxies,
                                                  recursive);

        if (!recursive) {
            break;
        }

        if (rc == NGX_DECLINED && found) {
            rc = NGX_DONE;
            break;
        }

        if (rc != NGX_OK) {
            break;
        }

        found = 1;
    }

    return rc;
}