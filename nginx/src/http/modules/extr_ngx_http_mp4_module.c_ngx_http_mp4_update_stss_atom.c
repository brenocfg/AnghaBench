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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {size_t sync_samples_entries; size_t start_sample; size_t size; TYPE_2__* out; } ;
typedef  TYPE_3__ ngx_http_mp4_trak_t ;
struct TYPE_14__ {size_t* size; size_t* entries; } ;
typedef  TYPE_4__ ngx_http_mp4_stss_atom_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;
struct TYPE_15__ {TYPE_1__ file; } ;
typedef  TYPE_5__ ngx_http_mp4_file_t ;
struct TYPE_16__ {int pos; int last; } ;
typedef  TYPE_6__ ngx_buf_t ;
struct TYPE_12__ {TYPE_6__* buf; } ;

/* Variables and functions */
 size_t NGX_HTTP_MP4_STSS_ATOM ; 
 size_t NGX_HTTP_MP4_STSS_DATA ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_mp4_crop_stss_data (TYPE_5__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 size_t ngx_mp4_get_32value (size_t*) ; 
 int /*<<< orphan*/  ngx_mp4_set_32value (size_t*,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mp4_update_stss_atom(ngx_http_mp4_file_t *mp4,
    ngx_http_mp4_trak_t *trak)
{
    size_t                     atom_size;
    uint32_t                   sample, start_sample, *entry, *end;
    ngx_buf_t                 *atom, *data;
    ngx_http_mp4_stss_atom_t  *stss_atom;

    /*
     * mdia.minf.stbl.stss updating requires trak->start_sample
     * from mdia.minf.stbl.stts which depends on value from mdia.mdhd
     * atom which may reside after mdia.minf
     */

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "mp4 stss atom update");

    data = trak->out[NGX_HTTP_MP4_STSS_DATA].buf;

    if (data == NULL) {
        return NGX_OK;
    }

    ngx_http_mp4_crop_stss_data(mp4, trak, 1);
    ngx_http_mp4_crop_stss_data(mp4, trak, 0);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "sync sample entries:%uD", trak->sync_samples_entries);

    if (trak->sync_samples_entries) {
        entry = (uint32_t *) data->pos;
        end = (uint32_t *) data->last;

        start_sample = trak->start_sample;

        while (entry < end) {
            sample = ngx_mp4_get_32value(entry);
            sample -= start_sample;
            ngx_mp4_set_32value(entry, sample);
            entry++;
        }

    } else {
        trak->out[NGX_HTTP_MP4_STSS_DATA].buf = NULL;
    }

    atom_size = sizeof(ngx_http_mp4_stss_atom_t) + (data->last - data->pos);
    trak->size += atom_size;

    atom = trak->out[NGX_HTTP_MP4_STSS_ATOM].buf;
    stss_atom = (ngx_http_mp4_stss_atom_t *) atom->pos;

    ngx_mp4_set_32value(stss_atom->size, atom_size);
    ngx_mp4_set_32value(stss_atom->entries, trak->sync_samples_entries);

    return NGX_OK;
}