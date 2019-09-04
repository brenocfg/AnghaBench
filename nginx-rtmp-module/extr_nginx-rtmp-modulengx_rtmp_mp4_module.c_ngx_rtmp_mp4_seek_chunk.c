#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_13__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_15__ {int chunk; scalar_t__ chunk_pos; scalar_t__ pos; scalar_t__ chunk_count; } ;
struct TYPE_14__ {TYPE_2__* chunks; int /*<<< orphan*/  id; TYPE_5__ cursor; } ;
typedef  TYPE_4__ ngx_rtmp_mp4_track_t ;
typedef  TYPE_5__ ngx_rtmp_mp4_cursor_t ;
struct TYPE_16__ {scalar_t__ first_chunk; scalar_t__ samples_per_chunk; } ;
typedef  TYPE_6__ ngx_rtmp_mp4_chunk_entry_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {scalar_t__ entry_count; TYPE_6__* entries; } ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_offset (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ ngx_rtmp_r32 (scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_seek_chunk(ngx_rtmp_session_t *s, ngx_rtmp_mp4_track_t *t)
{
    ngx_rtmp_mp4_cursor_t          *cr;
    ngx_rtmp_mp4_chunk_entry_t     *ce, *nce;
    ngx_uint_t                      pos, dpos, dchunk;

    cr = &t->cursor;

    if (t->chunks == NULL || t->chunks->entry_count == 0) {
        cr->chunk = 1;
        return NGX_OK;
    }

    ce = t->chunks->entries;
    pos = 0;

    while (cr->chunk_pos + 1 < ngx_rtmp_r32(t->chunks->entry_count)) {
        nce = ce + 1;

        dpos = (ngx_rtmp_r32(nce->first_chunk) -
                ngx_rtmp_r32(ce->first_chunk)) *
                ngx_rtmp_r32(ce->samples_per_chunk);

        if (pos + dpos > cr->pos) {
            break;
        }

        pos += dpos;
        ce++;
        cr->chunk_pos++;
    }

    if (ce->samples_per_chunk == 0) {
        return NGX_ERROR;
    }

    dchunk = (cr->pos - pos) / ngx_rtmp_r32(ce->samples_per_chunk);

    cr->chunk = ngx_rtmp_r32(ce->first_chunk) + dchunk;
    cr->chunk_pos = (ngx_uint_t) (ce - t->chunks->entries);
    cr->chunk_count = (ngx_uint_t) (cr->pos - pos - dchunk *
                                    ngx_rtmp_r32(ce->samples_per_chunk));

    ngx_log_debug7(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "mp4: track#%ui seek chunk[%ui/%uD][%uD..%ui][%ui/%uD]",
                   t->id, cr->chunk_pos,
                   ngx_rtmp_r32(t->chunks->entry_count),
                   ngx_rtmp_r32(ce->first_chunk),
                   cr->chunk, cr->chunk_count,
                   ngx_rtmp_r32(ce->samples_per_chunk));

    return ngx_rtmp_mp4_update_offset(s, t);
}