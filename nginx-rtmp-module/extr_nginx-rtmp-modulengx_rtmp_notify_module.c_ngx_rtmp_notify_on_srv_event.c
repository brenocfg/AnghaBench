#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_url_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_9__ {int len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_10__ {int /*<<< orphan*/ ** url; } ;
typedef  TYPE_3__ ngx_rtmp_notify_srv_conf_t ;
struct TYPE_11__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_8__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 size_t NGX_RTMP_NOTIFY_CONNECT ; 
 size_t NGX_RTMP_NOTIFY_DISCONNECT ; 
 int /*<<< orphan*/ * ngx_rtmp_notify_parse_url (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static char *
ngx_rtmp_notify_on_srv_event(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_rtmp_notify_srv_conf_t     *nscf = conf;

    ngx_str_t                      *name, *value;
    ngx_url_t                      *u;
    ngx_uint_t                      n;

    value = cf->args->elts;

    u = ngx_rtmp_notify_parse_url(cf, &value[1]);
    if (u == NULL) {
        return NGX_CONF_ERROR;
    }

    name = &value[0];

    n = 0;

    switch (name->len) {
        case sizeof("on_connect") - 1:
            n = NGX_RTMP_NOTIFY_CONNECT;
            break;

        case sizeof("on_disconnect") - 1:
            n = NGX_RTMP_NOTIFY_DISCONNECT;
            break;
    }

    nscf->url[n] = u;

    return NGX_CONF_OK;
}