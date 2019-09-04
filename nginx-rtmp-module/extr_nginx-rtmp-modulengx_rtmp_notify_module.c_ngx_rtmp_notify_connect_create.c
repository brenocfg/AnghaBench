#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_19__ {int /*<<< orphan*/  uri; int /*<<< orphan*/  host; } ;
typedef  TYPE_2__ ngx_url_t ;
struct TYPE_20__ {int len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_21__ {scalar_t__ epoch; TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_rtmp_session_t ;
struct TYPE_22__ {scalar_t__ method; TYPE_2__** url; } ;
typedef  TYPE_5__ ngx_rtmp_notify_srv_conf_t ;
struct TYPE_23__ {int /*<<< orphan*/ * args; int /*<<< orphan*/ * page_url; int /*<<< orphan*/ * tc_url; int /*<<< orphan*/ * swf_url; int /*<<< orphan*/ * flashver; int /*<<< orphan*/ * app; } ;
typedef  TYPE_6__ ngx_rtmp_connect_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_24__ {int /*<<< orphan*/ * next; TYPE_8__* buf; } ;
typedef  TYPE_7__ ngx_chain_t ;
struct TYPE_25__ {int /*<<< orphan*/ * last; } ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_18__ {TYPE_3__ addr_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ESCAPE_ARGS ; 
 int NGX_INT32_LEN ; 
 scalar_t__ NGX_RTMP_NETCALL_HTTP_POST ; 
 size_t NGX_RTMP_NOTIFY_CONNECT ; 
 TYPE_7__* ngx_alloc_chain_link (int /*<<< orphan*/ *) ; 
 void* ngx_cpymem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 TYPE_8__* ngx_create_temp_buf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ngx_escape_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_rtmp_get_module_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_rtmp_netcall_http_format_request (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_notify_module ; 
 int /*<<< orphan*/  ngx_rtmp_notify_urlencoded ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 size_t ngx_strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_chain_t *
ngx_rtmp_notify_connect_create(ngx_rtmp_session_t *s, void *arg,
        ngx_pool_t *pool)
{
    ngx_rtmp_connect_t             *v = arg;

    ngx_rtmp_notify_srv_conf_t     *nscf;
    ngx_url_t                      *url;
    ngx_chain_t                    *al, *bl;
    ngx_buf_t                      *b;
    ngx_str_t                      *addr_text;
    size_t                          app_len, args_len, flashver_len,
                                    swf_url_len, tc_url_len, page_url_len;

    nscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_notify_module);

    al = ngx_alloc_chain_link(pool);
    if (al == NULL) {
        return NULL;
    }

    /* these values are still missing in session
     * so we have to construct the request from
     * connection struct */

    app_len = ngx_strlen(v->app);
    args_len = ngx_strlen(v->args);
    flashver_len = ngx_strlen(v->flashver);
    swf_url_len = ngx_strlen(v->swf_url);
    tc_url_len = ngx_strlen(v->tc_url);
    page_url_len = ngx_strlen(v->page_url);

    addr_text = &s->connection->addr_text;

    b = ngx_create_temp_buf(pool,
            sizeof("call=connect") - 1 +
            sizeof("&app=") - 1 + app_len * 3 +
            sizeof("&flashver=") - 1 + flashver_len * 3 +
            sizeof("&swfurl=") - 1 + swf_url_len * 3 +
            sizeof("&tcurl=") - 1 + tc_url_len * 3 +
            sizeof("&pageurl=") - 1 + page_url_len * 3 +
            sizeof("&addr=") - 1 + addr_text->len * 3 +
            sizeof("&epoch=") - 1 + NGX_INT32_LEN +
            1 + args_len
        );

    if (b == NULL) {
        return NULL;
    }

    al->buf = b;
    al->next = NULL;

    b->last = ngx_cpymem(b->last, (u_char*) "app=", sizeof("app=") - 1);
    b->last = (u_char*) ngx_escape_uri(b->last, v->app, app_len,
                                       NGX_ESCAPE_ARGS);

    b->last = ngx_cpymem(b->last, (u_char*) "&flashver=",
                         sizeof("&flashver=") - 1);
    b->last = (u_char*) ngx_escape_uri(b->last, v->flashver, flashver_len,
                                       NGX_ESCAPE_ARGS);

    b->last = ngx_cpymem(b->last, (u_char*) "&swfurl=",
                         sizeof("&swfurl=") - 1);
    b->last = (u_char*) ngx_escape_uri(b->last, v->swf_url, swf_url_len,
                                       NGX_ESCAPE_ARGS);

    b->last = ngx_cpymem(b->last, (u_char*) "&tcurl=",
                         sizeof("&tcurl=") - 1);
    b->last = (u_char*) ngx_escape_uri(b->last, v->tc_url, tc_url_len,
                                       NGX_ESCAPE_ARGS);

    b->last = ngx_cpymem(b->last, (u_char*) "&pageurl=",
                         sizeof("&pageurl=") - 1);
    b->last = (u_char*) ngx_escape_uri(b->last, v->page_url, page_url_len,
                                       NGX_ESCAPE_ARGS);

    b->last = ngx_cpymem(b->last, (u_char*) "&addr=", sizeof("&addr=") -1);
    b->last = (u_char*) ngx_escape_uri(b->last, addr_text->data,
                                       addr_text->len, NGX_ESCAPE_ARGS);

    b->last = ngx_cpymem(b->last, (u_char*) "&epoch=", sizeof("&epoch=") -1);
    b->last = ngx_sprintf(b->last, "%uD", (uint32_t) s->epoch);

    b->last = ngx_cpymem(b->last, (u_char*) "&call=connect",
                         sizeof("&call=connect") - 1);

    if (args_len) {
        *b->last++ = '&';
        b->last = (u_char *) ngx_cpymem(b->last, v->args, args_len);
    }

    url = nscf->url[NGX_RTMP_NOTIFY_CONNECT];

    bl = NULL;

    if (nscf->method == NGX_RTMP_NETCALL_HTTP_POST) {
        bl = al;
        al = NULL;
    }

    return ngx_rtmp_netcall_http_format_request(nscf->method, &url->host,
                                                &url->uri, al, bl, pool,
                                                &ngx_rtmp_notify_urlencoded);
}