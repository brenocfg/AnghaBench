#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int stat; } ;
typedef  TYPE_1__ ngx_rtmp_stat_loc_conf_t ;
struct TYPE_8__ {int /*<<< orphan*/ * app_conf; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ngx_rtmp_core_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_10__ {size_t ctx_index; } ;
struct TYPE_9__ {size_t ctx_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_RTMP_STAT_ES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGX_RTMP_STAT_L (char*) ; 
 int NGX_RTMP_STAT_LIVE ; 
 int NGX_RTMP_STAT_PLAY ; 
 TYPE_1__* ngx_http_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__ ngx_rtmp_live_module ; 
 TYPE_4__ ngx_rtmp_play_module ; 
 int /*<<< orphan*/  ngx_rtmp_stat_live (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_stat_module ; 
 int /*<<< orphan*/  ngx_rtmp_stat_play (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_rtmp_stat_application(ngx_http_request_t *r, ngx_chain_t ***lll,
        ngx_rtmp_core_app_conf_t *cacf)
{
    ngx_rtmp_stat_loc_conf_t       *slcf;

    NGX_RTMP_STAT_L("<application>\r\n");
    NGX_RTMP_STAT_L("<name>");
    NGX_RTMP_STAT_ES(&cacf->name);
    NGX_RTMP_STAT_L("</name>\r\n");

    slcf = ngx_http_get_module_loc_conf(r, ngx_rtmp_stat_module);

    if (slcf->stat & NGX_RTMP_STAT_LIVE) {
        ngx_rtmp_stat_live(r, lll,
                cacf->app_conf[ngx_rtmp_live_module.ctx_index]);
    }

    if (slcf->stat & NGX_RTMP_STAT_PLAY) {
        ngx_rtmp_stat_play(r, lll,
                cacf->app_conf[ngx_rtmp_play_module.ctx_index]);
    }

    NGX_RTMP_STAT_L("</application>\r\n");
}