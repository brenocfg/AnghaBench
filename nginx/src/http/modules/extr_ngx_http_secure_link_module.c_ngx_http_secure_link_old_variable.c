#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_md5_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {size_t len; int valid; int not_found; scalar_t__* data; scalar_t__ no_cacheable; } ;
typedef  TYPE_3__ ngx_http_variable_value_t ;
struct TYPE_10__ {scalar_t__* data; size_t len; } ;
struct TYPE_12__ {TYPE_2__ secret; } ;
typedef  TYPE_4__ ngx_http_secure_link_conf_t ;
struct TYPE_9__ {scalar_t__* data; size_t len; } ;
struct TYPE_13__ {TYPE_1__ unparsed_uri; } ;
typedef  TYPE_5__ ngx_http_request_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_hextoi (scalar_t__*,int) ; 
 int /*<<< orphan*/  ngx_md5_final (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_md5_update (int /*<<< orphan*/ *,scalar_t__*,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_secure_link_old_variable(ngx_http_request_t *r,
    ngx_http_secure_link_conf_t *conf, ngx_http_variable_value_t *v,
    uintptr_t data)
{
    u_char      *p, *start, *end, *last;
    size_t       len;
    ngx_int_t    n;
    ngx_uint_t   i;
    ngx_md5_t    md5;
    u_char       hash[16];

    p = &r->unparsed_uri.data[1];
    last = r->unparsed_uri.data + r->unparsed_uri.len;

    while (p < last) {
        if (*p++ == '/') {
            start = p;
            goto md5_start;
        }
    }

    goto not_found;

md5_start:

    while (p < last) {
        if (*p++ == '/') {
            end = p - 1;
            goto url_start;
        }
    }

    goto not_found;

url_start:

    len = last - p;

    if (end - start != 32 || len == 0) {
        goto not_found;
    }

    ngx_md5_init(&md5);
    ngx_md5_update(&md5, p, len);
    ngx_md5_update(&md5, conf->secret.data, conf->secret.len);
    ngx_md5_final(hash, &md5);

    for (i = 0; i < 16; i++) {
        n = ngx_hextoi(&start[2 * i], 2);
        if (n == NGX_ERROR || n != hash[i]) {
            goto not_found;
        }
    }

    v->len = len;
    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->data = p;

    return NGX_OK;

not_found:

    v->not_found = 1;

    return NGX_OK;
}