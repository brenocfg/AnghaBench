#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct TYPE_18__ {scalar_t__ name; TYPE_2__* sockaddr; } ;
struct TYPE_22__ {int /*<<< orphan*/  uri; TYPE_3__ peer; int /*<<< orphan*/  schema; } ;
typedef  TYPE_7__ ngx_http_upstream_t ;
struct TYPE_21__ {TYPE_5__* referer; TYPE_4__* host; } ;
struct TYPE_15__ {scalar_t__* data; int len; } ;
struct TYPE_23__ {scalar_t__* request_start; TYPE_6__ headers_in; TYPE_7__* upstream; TYPE_10__ uri; TYPE_10__ request_line; TYPE_1__* header_in; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_24__ {TYPE_10__ server_name; } ;
typedef  TYPE_9__ ngx_http_core_srv_conf_t ;
struct TYPE_20__ {TYPE_10__ value; } ;
struct TYPE_19__ {TYPE_10__ value; } ;
struct TYPE_17__ {scalar_t__ sa_family; } ;
struct TYPE_16__ {scalar_t__* last; } ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 scalar_t__ CR ; 
 scalar_t__ LF ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_9__* ngx_http_get_module_srv_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__* ngx_snprintf (scalar_t__*,size_t,char*,TYPE_10__*,...) ; 

__attribute__((used)) static u_char *
ngx_http_log_error_handler(ngx_http_request_t *r, ngx_http_request_t *sr,
    u_char *buf, size_t len)
{
    char                      *uri_separator;
    u_char                    *p;
    ngx_http_upstream_t       *u;
    ngx_http_core_srv_conf_t  *cscf;

    cscf = ngx_http_get_module_srv_conf(r, ngx_http_core_module);

    p = ngx_snprintf(buf, len, ", server: %V", &cscf->server_name);
    len -= p - buf;
    buf = p;

    if (r->request_line.data == NULL && r->request_start) {
        for (p = r->request_start; p < r->header_in->last; p++) {
            if (*p == CR || *p == LF) {
                break;
            }
        }

        r->request_line.len = p - r->request_start;
        r->request_line.data = r->request_start;
    }

    if (r->request_line.len) {
        p = ngx_snprintf(buf, len, ", request: \"%V\"", &r->request_line);
        len -= p - buf;
        buf = p;
    }

    if (r != sr) {
        p = ngx_snprintf(buf, len, ", subrequest: \"%V\"", &sr->uri);
        len -= p - buf;
        buf = p;
    }

    u = sr->upstream;

    if (u && u->peer.name) {

        uri_separator = "";

#if (NGX_HAVE_UNIX_DOMAIN)
        if (u->peer.sockaddr && u->peer.sockaddr->sa_family == AF_UNIX) {
            uri_separator = ":";
        }
#endif

        p = ngx_snprintf(buf, len, ", upstream: \"%V%V%s%V\"",
                         &u->schema, u->peer.name,
                         uri_separator, &u->uri);
        len -= p - buf;
        buf = p;
    }

    if (r->headers_in.host) {
        p = ngx_snprintf(buf, len, ", host: \"%V\"",
                         &r->headers_in.host->value);
        len -= p - buf;
        buf = p;
    }

    if (r->headers_in.referer) {
        p = ngx_snprintf(buf, len, ", referrer: \"%V\"",
                         &r->headers_in.referer->value);
        buf = p;
    }

    return buf;
}