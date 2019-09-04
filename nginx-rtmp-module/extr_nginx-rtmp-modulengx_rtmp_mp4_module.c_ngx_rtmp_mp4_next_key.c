#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_12__ {int key; scalar_t__ key_pos; scalar_t__ pos; } ;
struct TYPE_11__ {TYPE_2__* keys; int /*<<< orphan*/  id; TYPE_5__ cursor; } ;
typedef  TYPE_4__ ngx_rtmp_mp4_track_t ;
typedef  TYPE_5__ ngx_rtmp_mp4_cursor_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int /*<<< orphan*/  entry_count; int /*<<< orphan*/ * entries; } ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,scalar_t__,scalar_t__,scalar_t__,char*) ; 
 scalar_t__ ngx_rtmp_r32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_next_key(ngx_rtmp_session_t *s, ngx_rtmp_mp4_track_t *t)
{
    ngx_rtmp_mp4_cursor_t          *cr;
    uint32_t                       *ke;

    cr = &t->cursor;

    if (t->keys == NULL) {
        return NGX_OK;
    }

    if (cr->key) {
        cr->key_pos++;
    }

    if (cr->key_pos >= ngx_rtmp_r32(t->keys->entry_count)) {
        ngx_log_debug3(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "mp4: track#%ui key[%ui/%uD] overflow",
                t->id, cr->key_pos,
                ngx_rtmp_r32(t->keys->entry_count));

        cr->key = 0;

        return NGX_OK;
    }

    ke = &t->keys->entries[cr->key_pos];
    cr->key = (cr->pos + 1 == ngx_rtmp_r32(*ke));

    ngx_log_debug6(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "mp4: track#%ui key[%ui/%uD][%ui/%uD]=%s",
                   t->id, cr->key_pos,
                   ngx_rtmp_r32(t->keys->entry_count),
                   cr->pos, ngx_rtmp_r32(*ke),
                   cr->key ? "match" : "miss");

    return NGX_OK;
}