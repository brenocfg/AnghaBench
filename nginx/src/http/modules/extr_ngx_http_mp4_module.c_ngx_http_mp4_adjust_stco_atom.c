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
struct TYPE_10__ {TYPE_2__* out; } ;
typedef  TYPE_3__ ngx_http_mp4_trak_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;
struct TYPE_11__ {TYPE_1__ file; } ;
typedef  TYPE_4__ ngx_http_mp4_file_t ;
struct TYPE_12__ {scalar_t__ last; scalar_t__ pos; } ;
typedef  TYPE_5__ ngx_buf_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_9__ {TYPE_5__* buf; } ;

/* Variables and functions */
 size_t NGX_HTTP_MP4_STCO_DATA ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_mp4_get_32value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_mp4_set_32value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_mp4_adjust_stco_atom(ngx_http_mp4_file_t *mp4,
    ngx_http_mp4_trak_t *trak, int32_t adjustment)
{
    uint32_t    offset, *entry, *end;
    ngx_buf_t  *data;

    /*
     * moov.trak.mdia.minf.stbl.stco adjustment requires
     * minimal start offset of all traks and new moov atom size
     */

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "mp4 stco atom adjustment");

    data = trak->out[NGX_HTTP_MP4_STCO_DATA].buf;
    entry = (uint32_t *) data->pos;
    end = (uint32_t *) data->last;

    while (entry < end) {
        offset = ngx_mp4_get_32value(entry);
        offset += adjustment;
        ngx_mp4_set_32value(entry, offset);
        entry++;
    }
}