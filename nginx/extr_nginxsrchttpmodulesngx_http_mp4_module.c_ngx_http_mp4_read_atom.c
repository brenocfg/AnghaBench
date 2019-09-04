#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ off_t ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_mp4_atom_header_t ;
typedef  int /*<<< orphan*/  ngx_mp4_atom_header64_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_1__ name; int /*<<< orphan*/  log; } ;
struct TYPE_12__ {int offset; TYPE_2__ file; int /*<<< orphan*/ * buffer_pos; } ;
typedef  TYPE_3__ ngx_http_mp4_file_t ;
struct TYPE_13__ {scalar_t__ (* handler ) (TYPE_3__*,int) ;scalar_t__ name; } ;
typedef  TYPE_4__ ngx_http_mp4_atom_handler_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_MAX_OFF_T_VALUE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_mp4_read (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_mp4_atom_next (TYPE_3__*,int) ; 
 int ngx_mp4_get_32value (int /*<<< orphan*/ *) ; 
 int ngx_mp4_get_64value (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ stub1 (TYPE_3__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mp4_read_atom(ngx_http_mp4_file_t *mp4,
    ngx_http_mp4_atom_handler_t *atom, uint64_t atom_data_size)
{
    off_t        end;
    size_t       atom_header_size;
    u_char      *atom_header, *atom_name;
    uint64_t     atom_size;
    ngx_int_t    rc;
    ngx_uint_t   n;

    end = mp4->offset + atom_data_size;

    while (mp4->offset < end) {

        if (ngx_http_mp4_read(mp4, sizeof(uint32_t)) != NGX_OK) {
            return NGX_ERROR;
        }

        atom_header = mp4->buffer_pos;
        atom_size = ngx_mp4_get_32value(atom_header);
        atom_header_size = sizeof(ngx_mp4_atom_header_t);

        if (atom_size == 0) {
            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                           "mp4 atom end");
            return NGX_OK;
        }

        if (atom_size < sizeof(ngx_mp4_atom_header_t)) {

            if (atom_size == 1) {

                if (ngx_http_mp4_read(mp4, sizeof(ngx_mp4_atom_header64_t))
                    != NGX_OK)
                {
                    return NGX_ERROR;
                }

                /* 64-bit atom size */
                atom_header = mp4->buffer_pos;
                atom_size = ngx_mp4_get_64value(atom_header + 8);
                atom_header_size = sizeof(ngx_mp4_atom_header64_t);

                if (atom_size < sizeof(ngx_mp4_atom_header64_t)) {
                    ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                                  "\"%s\" mp4 atom is too small:%uL",
                                  mp4->file.name.data, atom_size);
                    return NGX_ERROR;
                }

            } else {
                ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                              "\"%s\" mp4 atom is too small:%uL",
                              mp4->file.name.data, atom_size);
                return NGX_ERROR;
            }
        }

        if (ngx_http_mp4_read(mp4, sizeof(ngx_mp4_atom_header_t)) != NGX_OK) {
            return NGX_ERROR;
        }

        atom_header = mp4->buffer_pos;
        atom_name = atom_header + sizeof(uint32_t);

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                       "mp4 atom: %*s @%O:%uL",
                       (size_t) 4, atom_name, mp4->offset, atom_size);

        if (atom_size > (uint64_t) (NGX_MAX_OFF_T_VALUE - mp4->offset)
            || mp4->offset + (off_t) atom_size > end)
        {
            ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                          "\"%s\" mp4 atom too large:%uL",
                          mp4->file.name.data, atom_size);
            return NGX_ERROR;
        }

        for (n = 0; atom[n].name; n++) {

            if (ngx_strncmp(atom_name, atom[n].name, 4) == 0) {

                ngx_mp4_atom_next(mp4, atom_header_size);

                rc = atom[n].handler(mp4, atom_size - atom_header_size);
                if (rc != NGX_OK) {
                    return rc;
                }

                goto next;
            }
        }

        ngx_mp4_atom_next(mp4, atom_size);

    next:
        continue;
    }

    return NGX_OK;
}