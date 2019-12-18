#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {scalar_t__ fd; scalar_t__ size; int /*<<< orphan*/ * log; } ;
typedef  TYPE_1__ ngx_rtmp_mpegts_file_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_FILE_DEFAULT_ACCESS ; 
 int /*<<< orphan*/  NGX_FILE_TRUNCATE ; 
 int /*<<< orphan*/  NGX_FILE_WRONLY ; 
 scalar_t__ NGX_INVALID_FILE ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_close_file (scalar_t__) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_open_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_rtmp_mpegts_write_header (TYPE_1__*) ; 

ngx_int_t
ngx_rtmp_mpegts_open_file(ngx_rtmp_mpegts_file_t *file, u_char *path,
    ngx_log_t *log)
{
    file->log = log;

    file->fd = ngx_open_file(path, NGX_FILE_WRONLY, NGX_FILE_TRUNCATE,
                             NGX_FILE_DEFAULT_ACCESS);

    if (file->fd == NGX_INVALID_FILE) {
        ngx_log_error(NGX_LOG_ERR, log, ngx_errno,
                      "hls: error creating fragment file");
        return NGX_ERROR;
    }

    file->size = 0;

    if (ngx_rtmp_mpegts_write_header(file) != NGX_OK) {
        ngx_log_error(NGX_LOG_ERR, log, ngx_errno,
                      "hls: error writing fragment header");
        ngx_close_file(file->fd);
        return NGX_ERROR;
    }

    return NGX_OK;
}