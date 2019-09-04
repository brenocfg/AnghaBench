#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_handler_pt ;
struct TYPE_4__ {int /*<<< orphan*/  amf; int /*<<< orphan*/ * events; } ;
typedef  TYPE_1__ ngx_rtmp_core_main_conf_t ;
struct TYPE_5__ {void* handler; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ngx_rtmp_amf_handler_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 size_t NGX_RTMP_DISCONNECT ; 
 size_t NGX_RTMP_MSG_AUDIO ; 
 size_t NGX_RTMP_MSG_VIDEO ; 
 void* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_codec_av ; 
 int /*<<< orphan*/  ngx_rtmp_codec_disconnect ; 
 void* ngx_rtmp_codec_meta_data ; 
 TYPE_1__* ngx_rtmp_conf_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_codec_postconfiguration(ngx_conf_t *cf)
{
    ngx_rtmp_core_main_conf_t          *cmcf;
    ngx_rtmp_handler_pt                *h;
    ngx_rtmp_amf_handler_t             *ch;

    cmcf = ngx_rtmp_conf_get_module_main_conf(cf, ngx_rtmp_core_module);

    h = ngx_array_push(&cmcf->events[NGX_RTMP_MSG_AUDIO]);
    *h = ngx_rtmp_codec_av;

    h = ngx_array_push(&cmcf->events[NGX_RTMP_MSG_VIDEO]);
    *h = ngx_rtmp_codec_av;

    h = ngx_array_push(&cmcf->events[NGX_RTMP_DISCONNECT]);
    *h = ngx_rtmp_codec_disconnect;

    /* register metadata handler */
    ch = ngx_array_push(&cmcf->amf);
    if (ch == NULL) {
        return NGX_ERROR;
    }
    ngx_str_set(&ch->name, "@setDataFrame");
    ch->handler = ngx_rtmp_codec_meta_data;

    ch = ngx_array_push(&cmcf->amf);
    if (ch == NULL) {
        return NGX_ERROR;
    }
    ngx_str_set(&ch->name, "onMetaData");
    ch->handler = ngx_rtmp_codec_meta_data;


    return NGX_OK;
}