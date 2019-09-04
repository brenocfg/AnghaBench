#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  size; } ;
typedef  TYPE_4__ ngx_mp4_stts_atom_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_16__ {size_t time_to_sample_entries; size_t size; TYPE_3__* out; } ;
typedef  TYPE_5__ ngx_http_mp4_trak_t ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
struct TYPE_13__ {int /*<<< orphan*/  log; TYPE_1__ name; } ;
struct TYPE_17__ {TYPE_2__ file; } ;
typedef  TYPE_6__ ngx_http_mp4_file_t ;
struct TYPE_18__ {int last; int pos; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_14__ {TYPE_7__* buf; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 size_t NGX_HTTP_MP4_STTS_ATOM ; 
 size_t NGX_HTTP_MP4_STTS_DATA ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_mp4_crop_stts_data (TYPE_6__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mp4_set_32value (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mp4_update_stts_atom(ngx_http_mp4_file_t *mp4,
    ngx_http_mp4_trak_t *trak)
{
    size_t                atom_size;
    ngx_buf_t            *atom, *data;
    ngx_mp4_stts_atom_t  *stts_atom;

    /*
     * mdia.minf.stbl.stts updating requires trak->timescale
     * from mdia.mdhd atom which may reside after mdia.minf
     */

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "mp4 stts atom update");

    data = trak->out[NGX_HTTP_MP4_STTS_DATA].buf;

    if (data == NULL) {
        ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                      "no mp4 stts atoms were found in \"%s\"",
                      mp4->file.name.data);
        return NGX_ERROR;
    }

    if (ngx_http_mp4_crop_stts_data(mp4, trak, 1) != NGX_OK) {
        return NGX_ERROR;
    }

    if (ngx_http_mp4_crop_stts_data(mp4, trak, 0) != NGX_OK) {
        return NGX_ERROR;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "time-to-sample entries:%uD", trak->time_to_sample_entries);

    atom_size = sizeof(ngx_mp4_stts_atom_t) + (data->last - data->pos);
    trak->size += atom_size;

    atom = trak->out[NGX_HTTP_MP4_STTS_ATOM].buf;
    stts_atom = (ngx_mp4_stts_atom_t *) atom->pos;
    ngx_mp4_set_32value(stts_atom->size, atom_size);
    ngx_mp4_set_32value(stts_atom->entries, trak->time_to_sample_entries);

    return NGX_OK;
}