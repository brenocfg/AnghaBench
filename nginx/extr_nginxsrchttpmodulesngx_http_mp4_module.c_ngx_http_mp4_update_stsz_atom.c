#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  size; } ;
typedef  TYPE_4__ ngx_mp4_stsz_atom_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {int sample_sizes_entries; int start_sample; int* start_chunk_samples; int end_sample; int* end_chunk_samples; size_t size; TYPE_3__* out; int /*<<< orphan*/  end_chunk_samples_size; int /*<<< orphan*/  start_chunk_samples_size; } ;
typedef  TYPE_5__ ngx_http_mp4_trak_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int /*<<< orphan*/  log; TYPE_1__ name; } ;
struct TYPE_15__ {TYPE_2__ file; scalar_t__ length; } ;
typedef  TYPE_6__ ngx_http_mp4_file_t ;
struct TYPE_16__ {int pos; int last; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_12__ {TYPE_7__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 size_t NGX_HTTP_MP4_STSZ_ATOM ; 
 size_t NGX_HTTP_MP4_STSZ_DATA ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_mp4_get_32value (int*) ; 
 int /*<<< orphan*/  ngx_mp4_set_32value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mp4_update_stsz_atom(ngx_http_mp4_file_t *mp4,
    ngx_http_mp4_trak_t *trak)
{
    size_t                atom_size;
    uint32_t             *pos, *end, entries;
    ngx_buf_t            *atom, *data;
    ngx_mp4_stsz_atom_t  *stsz_atom;

    /*
     * mdia.minf.stbl.stsz updating requires trak->start_sample
     * from mdia.minf.stbl.stts which depends on value from mdia.mdhd
     * atom which may reside after mdia.minf
     */

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "mp4 stsz atom update");

    data = trak->out[NGX_HTTP_MP4_STSZ_DATA].buf;

    if (data) {
        entries = trak->sample_sizes_entries;

        if (trak->start_sample > entries) {
            ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                          "start time is out mp4 stsz samples in \"%s\"",
                          mp4->file.name.data);
            return NGX_ERROR;
        }

        entries -= trak->start_sample;
        data->pos += trak->start_sample * sizeof(uint32_t);
        end = (uint32_t *) data->pos;

        for (pos = end - trak->start_chunk_samples; pos < end; pos++) {
            trak->start_chunk_samples_size += ngx_mp4_get_32value(pos);
        }

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                       "chunk samples sizes:%uL",
                       trak->start_chunk_samples_size);

        if (mp4->length) {
            if (trak->end_sample - trak->start_sample > entries) {
                ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                              "end time is out mp4 stsz samples in \"%s\"",
                              mp4->file.name.data);
                return NGX_ERROR;
            }

            entries = trak->end_sample - trak->start_sample;
            data->last = data->pos + entries * sizeof(uint32_t);
            end = (uint32_t *) data->last;

            for (pos = end - trak->end_chunk_samples; pos < end; pos++) {
                trak->end_chunk_samples_size += ngx_mp4_get_32value(pos);
            }

            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                           "mp4 stsz end_chunk_samples_size:%uL",
                           trak->end_chunk_samples_size);
        }

        atom_size = sizeof(ngx_mp4_stsz_atom_t) + (data->last - data->pos);
        trak->size += atom_size;

        atom = trak->out[NGX_HTTP_MP4_STSZ_ATOM].buf;
        stsz_atom = (ngx_mp4_stsz_atom_t *) atom->pos;

        ngx_mp4_set_32value(stsz_atom->size, atom_size);
        ngx_mp4_set_32value(stsz_atom->entries, entries);
    }

    return NGX_OK;
}