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
struct TYPE_14__ {scalar_t__ time_pos; int not_first; scalar_t__ time_count; int /*<<< orphan*/  pos; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  last_timestamp; } ;
struct TYPE_12__ {TYPE_2__* times; int /*<<< orphan*/  id; TYPE_6__ cursor; } ;
typedef  TYPE_4__ ngx_rtmp_mp4_track_t ;
struct TYPE_13__ {int /*<<< orphan*/  sample_count; int /*<<< orphan*/  sample_delta; } ;
typedef  TYPE_5__ ngx_rtmp_mp4_time_entry_t ;
typedef  TYPE_6__ ngx_rtmp_mp4_cursor_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  entry_count; TYPE_5__* entries; } ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_rtmp_r32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_next_time(ngx_rtmp_session_t *s, ngx_rtmp_mp4_track_t *t)
{
    ngx_rtmp_mp4_cursor_t      *cr;
    ngx_rtmp_mp4_time_entry_t  *te;

    if (t->times == NULL) {
        return NGX_ERROR;
    }

    cr = &t->cursor;

    if (cr->time_pos >= ngx_rtmp_r32(t->times->entry_count)) {
        ngx_log_debug3(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                       "mp4: track#%ui time[%ui/%uD] overflow",
                       t->id, cr->time_pos,
                       ngx_rtmp_r32(t->times->entry_count));

        return NGX_ERROR;
    }

    te = &t->times->entries[cr->time_pos];

    cr->last_timestamp = cr->timestamp;
    cr->timestamp += ngx_rtmp_r32(te->sample_delta);

    cr->not_first = 1;

    ngx_log_debug8(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "mp4: track#%ui time[%ui] [%ui/%uD][%ui/%uD]=%uD t=%uD",
                   t->id, cr->pos, cr->time_pos,
                   ngx_rtmp_r32(t->times->entry_count),
                   cr->time_count, ngx_rtmp_r32(te->sample_count),
                   ngx_rtmp_r32(te->sample_delta),
                   cr->timestamp);

    cr->time_count++;
    cr->pos++;

    if (cr->time_count >= ngx_rtmp_r32(te->sample_count)) {
        cr->time_pos++;
        cr->time_count = 0;
    }

    return NGX_OK;
}