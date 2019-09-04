#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  fmts; } ;
typedef  TYPE_1__ ngx_rtmp_play_main_conf_t ;
struct TYPE_10__ {int /*<<< orphan*/  send; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  seek; int /*<<< orphan*/  done; int /*<<< orphan*/  init; int /*<<< orphan*/  sfx; int /*<<< orphan*/  pfx; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ngx_rtmp_play_fmt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__** ngx_array_push (int /*<<< orphan*/ *) ; 
 TYPE_2__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ngx_rtmp_conf_get_module_main_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_done ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_init ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_seek ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_send ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_start ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_stop ; 
 int /*<<< orphan*/  ngx_rtmp_play_module ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_postconfiguration(ngx_conf_t *cf)
{
    ngx_rtmp_play_main_conf_t      *pmcf;
    ngx_rtmp_play_fmt_t           **pfmt, *fmt;

    pmcf = ngx_rtmp_conf_get_module_main_conf(cf, ngx_rtmp_play_module);

    pfmt = ngx_array_push(&pmcf->fmts);

    if (pfmt == NULL) {
        return NGX_ERROR;
    }

    fmt = ngx_pcalloc(cf->pool, sizeof(ngx_rtmp_play_fmt_t));

    if (fmt == NULL) {
        return NGX_ERROR;
    }

    *pfmt = fmt;

    ngx_str_set(&fmt->name, "mp4-format");

    ngx_str_set(&fmt->pfx, "mp4:");
    ngx_str_set(&fmt->sfx, ".mp4");

    fmt->init  = ngx_rtmp_mp4_init;
    fmt->done  = ngx_rtmp_mp4_done;
    fmt->seek  = ngx_rtmp_mp4_seek;
    fmt->start = ngx_rtmp_mp4_start;
    fmt->stop  = ngx_rtmp_mp4_stop;
    fmt->send  = ngx_rtmp_mp4_send;

    return NGX_OK;
}