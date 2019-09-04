#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_mp4_atom_header_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {TYPE_6__* buf; } ;
struct TYPE_15__ {int temporary; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_1__ name; int /*<<< orphan*/  log; } ;
struct TYPE_14__ {scalar_t__ buffer_end; size_t ftyp_size; size_t content_length; TYPE_4__ ftyp_atom; TYPE_6__ ftyp_atom_buf; TYPE_3__* request; TYPE_2__ file; } ;
typedef  TYPE_5__ ngx_http_mp4_file_t ;
typedef  TYPE_6__ ngx_buf_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 scalar_t__ ngx_mp4_atom_data (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_mp4_atom_next (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ngx_mp4_set_32value (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_mp4_set_atom_name (int /*<<< orphan*/ *,float,char,char,char) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mp4_read_ftyp_atom(ngx_http_mp4_file_t *mp4, uint64_t atom_data_size)
{
    u_char     *ftyp_atom;
    size_t      atom_size;
    ngx_buf_t  *atom;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0, "mp4 ftyp atom");

    if (atom_data_size > 1024
        || ngx_mp4_atom_data(mp4) + (size_t) atom_data_size > mp4->buffer_end)
    {
        ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                      "\"%s\" mp4 ftyp atom is too large:%uL",
                      mp4->file.name.data, atom_data_size);
        return NGX_ERROR;
    }

    atom_size = sizeof(ngx_mp4_atom_header_t) + (size_t) atom_data_size;

    ftyp_atom = ngx_palloc(mp4->request->pool, atom_size);
    if (ftyp_atom == NULL) {
        return NGX_ERROR;
    }

    ngx_mp4_set_32value(ftyp_atom, atom_size);
    ngx_mp4_set_atom_name(ftyp_atom, 'f', 't', 'y', 'p');

    /*
     * only moov atom content is guaranteed to be in mp4->buffer
     * during sending response, so ftyp atom content should be copied
     */
    ngx_memcpy(ftyp_atom + sizeof(ngx_mp4_atom_header_t),
               ngx_mp4_atom_data(mp4), (size_t) atom_data_size);

    atom = &mp4->ftyp_atom_buf;
    atom->temporary = 1;
    atom->pos = ftyp_atom;
    atom->last = ftyp_atom + atom_size;

    mp4->ftyp_atom.buf = atom;
    mp4->ftyp_size = atom_size;
    mp4->content_length = atom_size;

    ngx_mp4_atom_next(mp4, atom_data_size);

    return NGX_OK;
}