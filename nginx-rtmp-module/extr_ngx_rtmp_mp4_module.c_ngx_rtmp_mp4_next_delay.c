#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_14__ {scalar_t__ delay_pos; scalar_t__ delay_count; scalar_t__ delay; } ;
struct TYPE_12__ {TYPE_2__* delays; int /*<<< orphan*/  id; TYPE_6__ cursor; } ;
typedef  TYPE_4__ ngx_rtmp_mp4_track_t ;
struct TYPE_13__ {int /*<<< orphan*/  sample_count; int /*<<< orphan*/  sample_offset; } ;
typedef  TYPE_5__ ngx_rtmp_mp4_delay_entry_t ;
typedef  TYPE_6__ ngx_rtmp_mp4_cursor_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  entry_count; TYPE_5__* entries; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ ngx_rtmp_r32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_next_delay(ngx_rtmp_session_t *s, ngx_rtmp_mp4_track_t *t)
{
    ngx_rtmp_mp4_cursor_t          *cr;
    ngx_rtmp_mp4_delay_entry_t     *de;

    cr = &t->cursor;

    if (t->delays == NULL) {
        return NGX_OK;
    }

    if (cr->delay_pos >= ngx_rtmp_r32(t->delays->entry_count)) {
        ngx_log_debug3(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "mp4: track#%ui delay[%ui/%uD] overflow",
                t->id, cr->delay_pos,
                ngx_rtmp_r32(t->delays->entry_count));

        return NGX_OK;
    }

    cr->delay_count++;
    de = &t->delays->entries[cr->delay_pos];

    if (cr->delay_count >= ngx_rtmp_r32(de->sample_count)) {
        cr->delay_pos++;
        de++;
        cr->delay_count = 0;
    }

    if (cr->delay_pos >= ngx_rtmp_r32(t->delays->entry_count)) {
        ngx_log_debug3(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "mp4: track#%ui delay[%ui/%uD] overflow",
                t->id, cr->delay_pos,
                ngx_rtmp_r32(t->delays->entry_count));

        return NGX_OK;
    }

    cr->delay = ngx_rtmp_r32(de->sample_offset);

    ngx_log_debug6(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "mp4: track#%ui delay[%ui/%uD][%ui/%uD]=%ui",
                   t->id, cr->delay_pos,
                   ngx_rtmp_r32(t->delays->entry_count),
                   cr->delay_count,
                   ngx_rtmp_r32(de->sample_count), cr->delay);

    return NGX_OK;
}