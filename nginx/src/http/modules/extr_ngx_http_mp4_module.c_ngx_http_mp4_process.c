#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_9__ ;
typedef  struct TYPE_49__   TYPE_8__ ;
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_1__ ;
typedef  struct TYPE_41__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
typedef  size_t ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_48__ {scalar_t__ size; scalar_t__ mdhd_size; scalar_t__ hdlr_size; scalar_t__ tkhd_size; scalar_t__ start_offset; scalar_t__ end_offset; TYPE_10__* out; } ;
typedef  TYPE_7__ ngx_http_mp4_trak_t ;
struct TYPE_47__ {size_t nelts; TYPE_7__* elts; } ;
struct TYPE_44__ {int /*<<< orphan*/  data; } ;
struct TYPE_45__ {int /*<<< orphan*/  log; TYPE_3__ name; } ;
struct TYPE_43__ {TYPE_1__* buf; } ;
struct TYPE_41__ {int /*<<< orphan*/ * buf; struct TYPE_41__* next; } ;
struct TYPE_46__ {scalar_t__ last; scalar_t__ pos; } ;
struct TYPE_49__ {scalar_t__ end; scalar_t__ moov_size; scalar_t__ ftyp_size; TYPE_6__ trak; TYPE_4__ file; TYPE_2__ mdat_data; TYPE_10__ mdat_atom; int /*<<< orphan*/  content_length; int /*<<< orphan*/  moov_atom_header; TYPE_10__ mvhd_atom; TYPE_5__ mvhd_atom_buf; TYPE_10__ moov_atom; TYPE_10__ ftyp_atom; TYPE_10__* out; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  request; int /*<<< orphan*/  length; int /*<<< orphan*/  start; } ;
typedef  TYPE_8__ ngx_http_mp4_file_t ;
struct TYPE_50__ {int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_9__ ngx_http_mp4_conf_t ;
typedef  TYPE_10__ ngx_chain_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_42__ {scalar_t__ file_last; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 size_t NGX_HTTP_MP4_CO64_DATA ; 
 size_t NGX_HTTP_MP4_LAST_ATOM ; 
 size_t NGX_HTTP_MP4_TRAK_ATOM ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_9__* ngx_http_get_module_loc_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_mp4_adjust_co64_atom (TYPE_8__*,TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_mp4_adjust_stco_atom (TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_mp4_atoms ; 
 int /*<<< orphan*/  ngx_http_mp4_module ; 
 scalar_t__ ngx_http_mp4_read_atom (TYPE_8__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ngx_http_mp4_update_co64_atom (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_mp4_update_ctts_atom (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_http_mp4_update_mdat_atom (TYPE_8__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_mp4_update_mdia_atom (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_mp4_update_minf_atom (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_mp4_update_stbl_atom (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_http_mp4_update_stco_atom (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_http_mp4_update_stsc_atom (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_http_mp4_update_stss_atom (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_http_mp4_update_stsz_atom (TYPE_8__*,TYPE_7__*) ; 
 scalar_t__ ngx_http_mp4_update_stts_atom (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_mp4_update_trak_atom (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mp4_set_32value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_mp4_set_atom_name (int /*<<< orphan*/ ,char,char,char,char) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mp4_process(ngx_http_mp4_file_t *mp4)
{
    off_t                  start_offset, end_offset, adjustment;
    ngx_int_t              rc;
    ngx_uint_t             i, j;
    ngx_chain_t          **prev;
    ngx_http_mp4_trak_t   *trak;
    ngx_http_mp4_conf_t   *conf;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "mp4 start:%ui, length:%ui", mp4->start, mp4->length);

    conf = ngx_http_get_module_loc_conf(mp4->request, ngx_http_mp4_module);

    mp4->buffer_size = conf->buffer_size;

    rc = ngx_http_mp4_read_atom(mp4, ngx_http_mp4_atoms, mp4->end);
    if (rc != NGX_OK) {
        return rc;
    }

    if (mp4->trak.nelts == 0) {
        ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                      "no mp4 trak atoms were found in \"%s\"",
                      mp4->file.name.data);
        return NGX_ERROR;
    }

    if (mp4->mdat_atom.buf == NULL) {
        ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                      "no mp4 mdat atom was found in \"%s\"",
                      mp4->file.name.data);
        return NGX_ERROR;
    }

    prev = &mp4->out;

    if (mp4->ftyp_atom.buf) {
        *prev = &mp4->ftyp_atom;
        prev = &mp4->ftyp_atom.next;
    }

    *prev = &mp4->moov_atom;
    prev = &mp4->moov_atom.next;

    if (mp4->mvhd_atom.buf) {
        mp4->moov_size += mp4->mvhd_atom_buf.last - mp4->mvhd_atom_buf.pos;
        *prev = &mp4->mvhd_atom;
        prev = &mp4->mvhd_atom.next;
    }

    start_offset = mp4->end;
    end_offset = 0;
    trak = mp4->trak.elts;

    for (i = 0; i < mp4->trak.nelts; i++) {

        if (ngx_http_mp4_update_stts_atom(mp4, &trak[i]) != NGX_OK) {
            return NGX_ERROR;
        }

        if (ngx_http_mp4_update_stss_atom(mp4, &trak[i]) != NGX_OK) {
            return NGX_ERROR;
        }

        ngx_http_mp4_update_ctts_atom(mp4, &trak[i]);

        if (ngx_http_mp4_update_stsc_atom(mp4, &trak[i]) != NGX_OK) {
            return NGX_ERROR;
        }

        if (ngx_http_mp4_update_stsz_atom(mp4, &trak[i]) != NGX_OK) {
            return NGX_ERROR;
        }

        if (trak[i].out[NGX_HTTP_MP4_CO64_DATA].buf) {
            if (ngx_http_mp4_update_co64_atom(mp4, &trak[i]) != NGX_OK) {
                return NGX_ERROR;
            }

        } else {
            if (ngx_http_mp4_update_stco_atom(mp4, &trak[i]) != NGX_OK) {
                return NGX_ERROR;
            }
        }

        ngx_http_mp4_update_stbl_atom(mp4, &trak[i]);
        ngx_http_mp4_update_minf_atom(mp4, &trak[i]);
        trak[i].size += trak[i].mdhd_size;
        trak[i].size += trak[i].hdlr_size;
        ngx_http_mp4_update_mdia_atom(mp4, &trak[i]);
        trak[i].size += trak[i].tkhd_size;
        ngx_http_mp4_update_trak_atom(mp4, &trak[i]);

        mp4->moov_size += trak[i].size;

        if (start_offset > trak[i].start_offset) {
            start_offset = trak[i].start_offset;
        }

        if (end_offset < trak[i].end_offset) {
            end_offset = trak[i].end_offset;
        }

        *prev = &trak[i].out[NGX_HTTP_MP4_TRAK_ATOM];
        prev = &trak[i].out[NGX_HTTP_MP4_TRAK_ATOM].next;

        for (j = 0; j < NGX_HTTP_MP4_LAST_ATOM + 1; j++) {
            if (trak[i].out[j].buf) {
                *prev = &trak[i].out[j];
                prev = &trak[i].out[j].next;
            }
        }
    }

    if (end_offset < start_offset) {
        end_offset = start_offset;
    }

    mp4->moov_size += 8;

    ngx_mp4_set_32value(mp4->moov_atom_header, mp4->moov_size);
    ngx_mp4_set_atom_name(mp4->moov_atom_header, 'm', 'o', 'o', 'v');
    mp4->content_length += mp4->moov_size;

    *prev = &mp4->mdat_atom;

    if (start_offset > mp4->mdat_data.buf->file_last) {
        ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                      "start time is out mp4 mdat atom in \"%s\"",
                      mp4->file.name.data);
        return NGX_ERROR;
    }

    adjustment = mp4->ftyp_size + mp4->moov_size
                 + ngx_http_mp4_update_mdat_atom(mp4, start_offset, end_offset)
                 - start_offset;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "mp4 adjustment:%O", adjustment);

    for (i = 0; i < mp4->trak.nelts; i++) {
        if (trak[i].out[NGX_HTTP_MP4_CO64_DATA].buf) {
            ngx_http_mp4_adjust_co64_atom(mp4, &trak[i], adjustment);
        } else {
            ngx_http_mp4_adjust_stco_atom(mp4, &trak[i], (int32_t) adjustment);
        }
    }

    return NGX_OK;
}