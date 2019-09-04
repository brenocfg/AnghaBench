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
struct TYPE_9__ {int len; char* data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_10__ {int /*<<< orphan*/ ** url; } ;
typedef  TYPE_3__ ngx_rtmp_notify_app_conf_t ;
struct TYPE_11__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_8__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 size_t NGX_RTMP_NOTIFY_DONE ; 
 size_t NGX_RTMP_NOTIFY_PLAY ; 
 size_t NGX_RTMP_NOTIFY_PLAY_DONE ; 
 size_t NGX_RTMP_NOTIFY_PUBLISH ; 
 size_t NGX_RTMP_NOTIFY_PUBLISH_DONE ; 
 size_t NGX_RTMP_NOTIFY_RECORD_DONE ; 
 size_t NGX_RTMP_NOTIFY_UPDATE ; 
 int /*<<< orphan*/ * ngx_rtmp_notify_parse_url (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static char *
ngx_rtmp_notify_on_app_event(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_rtmp_notify_app_conf_t     *nacf = conf;

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
        case sizeof("on_done") - 1: /* and on_play */
            if (name->data[3] == 'd') {
                n = NGX_RTMP_NOTIFY_DONE;
            } else {
                n = NGX_RTMP_NOTIFY_PLAY;
            }
            break;

        case sizeof("on_update") - 1:
            n = NGX_RTMP_NOTIFY_UPDATE;
            break;

        case sizeof("on_publish") - 1:
            n = NGX_RTMP_NOTIFY_PUBLISH;
            break;

        case sizeof("on_play_done") - 1:
            n = NGX_RTMP_NOTIFY_PLAY_DONE;
            break;

        case sizeof("on_record_done") - 1:
            n = NGX_RTMP_NOTIFY_RECORD_DONE;
            break;

        case sizeof("on_publish_done") - 1:
            n = NGX_RTMP_NOTIFY_PUBLISH_DONE;
            break;
    }

    nacf->url[n] = u;

    return NGX_CONF_OK;
}