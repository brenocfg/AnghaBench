#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_12__ {size_t len; char* data; } ;
struct TYPE_14__ {TYPE_3__ value; } ;
typedef  TYPE_5__ ngx_table_elt_t ;
typedef  int ngx_int_t ;
struct TYPE_10__ {TYPE_5__* x_accel_expires; } ;
struct TYPE_15__ {int /*<<< orphan*/  cacheable; TYPE_2__* conf; TYPE_1__ headers_in; } ;
typedef  TYPE_6__ ngx_http_upstream_t ;
struct TYPE_16__ {TYPE_4__* cache; TYPE_6__* upstream; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_13__ {int valid_sec; } ;
struct TYPE_11__ {int ignore_headers; } ;

/* Variables and functions */
#define  NGX_ERROR 128 
 int NGX_HTTP_UPSTREAM_IGN_XA_EXPIRES ; 
 int NGX_OK ; 
 int ngx_atoi (char*,size_t) ; 
 int /*<<< orphan*/  ngx_time () ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_process_accel_expires(ngx_http_request_t *r,
    ngx_table_elt_t *h, ngx_uint_t offset)
{
    ngx_http_upstream_t  *u;

    u = r->upstream;
    u->headers_in.x_accel_expires = h;

#if (NGX_HTTP_CACHE)
    {
    u_char     *p;
    size_t      len;
    ngx_int_t   n;

    if (u->conf->ignore_headers & NGX_HTTP_UPSTREAM_IGN_XA_EXPIRES) {
        return NGX_OK;
    }

    if (r->cache == NULL) {
        return NGX_OK;
    }

    len = h->value.len;
    p = h->value.data;

    if (p[0] != '@') {
        n = ngx_atoi(p, len);

        switch (n) {
        case 0:
            u->cacheable = 0;
            /* fall through */

        case NGX_ERROR:
            return NGX_OK;

        default:
            r->cache->valid_sec = ngx_time() + n;
            return NGX_OK;
        }
    }

    p++;
    len--;

    n = ngx_atoi(p, len);

    if (n != NGX_ERROR) {
        r->cache->valid_sec = n;
    }
    }
#endif

    return NGX_OK;
}