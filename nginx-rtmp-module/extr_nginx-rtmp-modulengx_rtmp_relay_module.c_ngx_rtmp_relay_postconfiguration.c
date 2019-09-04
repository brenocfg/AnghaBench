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
struct TYPE_5__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ngx_rtmp_amf_handler_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 size_t NGX_RTMP_HANDSHAKE_DONE ; 
 int /*<<< orphan*/  next_close_stream ; 
 int /*<<< orphan*/  next_delete_stream ; 
 int /*<<< orphan*/  next_play ; 
 int /*<<< orphan*/  next_publish ; 
 void* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_close_stream ; 
 TYPE_1__* ngx_rtmp_conf_get_module_main_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 int /*<<< orphan*/  ngx_rtmp_delete_stream ; 
 int /*<<< orphan*/  ngx_rtmp_play ; 
 int /*<<< orphan*/  ngx_rtmp_publish ; 
 int /*<<< orphan*/  ngx_rtmp_relay_close_stream ; 
 int /*<<< orphan*/  ngx_rtmp_relay_delete_stream ; 
 int /*<<< orphan*/  ngx_rtmp_relay_handshake_done ; 
 int /*<<< orphan*/  ngx_rtmp_relay_on_error ; 
 int /*<<< orphan*/  ngx_rtmp_relay_on_result ; 
 int /*<<< orphan*/  ngx_rtmp_relay_on_status ; 
 int /*<<< orphan*/  ngx_rtmp_relay_play ; 
 int /*<<< orphan*/  ngx_rtmp_relay_publish ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_relay_postconfiguration(ngx_conf_t *cf)
{
    ngx_rtmp_core_main_conf_t          *cmcf;
    ngx_rtmp_handler_pt                *h;
    ngx_rtmp_amf_handler_t             *ch;

    cmcf = ngx_rtmp_conf_get_module_main_conf(cf, ngx_rtmp_core_module);


    h = ngx_array_push(&cmcf->events[NGX_RTMP_HANDSHAKE_DONE]);
    *h = ngx_rtmp_relay_handshake_done;


    next_publish = ngx_rtmp_publish;
    ngx_rtmp_publish = ngx_rtmp_relay_publish;

    next_play = ngx_rtmp_play;
    ngx_rtmp_play = ngx_rtmp_relay_play;

    next_delete_stream = ngx_rtmp_delete_stream;
    ngx_rtmp_delete_stream = ngx_rtmp_relay_delete_stream;

    next_close_stream = ngx_rtmp_close_stream;
    ngx_rtmp_close_stream = ngx_rtmp_relay_close_stream;


    ch = ngx_array_push(&cmcf->amf);
    ngx_str_set(&ch->name, "_result");
    ch->handler = ngx_rtmp_relay_on_result;

    ch = ngx_array_push(&cmcf->amf);
    ngx_str_set(&ch->name, "_error");
    ch->handler = ngx_rtmp_relay_on_error;

    ch = ngx_array_push(&cmcf->amf);
    ngx_str_set(&ch->name, "onStatus");
    ch->handler = ngx_rtmp_relay_on_status;

    return NGX_OK;
}