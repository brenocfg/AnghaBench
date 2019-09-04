#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_3__ {char* data; int len; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  scalar_t__ ngx_fd_t ;

/* Variables and functions */
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_FILE_APPEND ; 
 scalar_t__ NGX_FILE_CREATE_OR_OPEN ; 
 int /*<<< orphan*/  NGX_FILE_DEFAULT_ACCESS ; 
 scalar_t__ NGX_FILE_OPEN ; 
 scalar_t__ NGX_FILE_RDONLY ; 
 scalar_t__ NGX_FILE_TRUNCATE ; 
 scalar_t__ NGX_FILE_WRONLY ; 
 scalar_t__ NGX_INVALID_FILE ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  dup2 (scalar_t__,scalar_t__) ; 
 int ngx_atoi (char*,int) ; 
 int /*<<< orphan*/  ngx_close_file (scalar_t__) ; 
 scalar_t__ ngx_open_file (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_rtmp_eval_streams(ngx_str_t *in)
{
#if !(NGX_WIN32)
    ngx_int_t   mode, create, v, close_src;
    ngx_fd_t    dst, src;
    u_char     *path;

    path = in->data;

    while (*path >= '0' && *path <= '9') {
        path++;
    }

    switch ((char) *path) {

        case '>':

            v = (path == in->data ? 1 : ngx_atoi(in->data, path - in->data));
            if (v == NGX_ERROR) {
                return NGX_ERROR;
            }

            dst = (ngx_fd_t) v;
            mode = NGX_FILE_WRONLY;
            create = NGX_FILE_TRUNCATE;
            path++;

            if (*path == (u_char) '>') {
                mode = NGX_FILE_APPEND;
                create = NGX_FILE_CREATE_OR_OPEN;
                path++;
            }

            break;

        case '<':

            v = (path == in->data ? 0 : ngx_atoi(in->data, path - in->data));
            if (v == NGX_ERROR) {
                return NGX_ERROR;
            }

            dst = (ngx_fd_t) v;
            mode = NGX_FILE_RDONLY;
            create = NGX_FILE_OPEN;
            path++;

            break;

        default:

            return NGX_DONE;
    }

    if (*path == (u_char) '&') {

        path++;
        v = ngx_atoi(path, in->data + in->len - path);
        if (v == NGX_ERROR) {
            return NGX_ERROR;
        }
        src = (ngx_fd_t) v;
        close_src = 0;

    } else {

        src = ngx_open_file(path, mode, create, NGX_FILE_DEFAULT_ACCESS);
        if (src == NGX_INVALID_FILE) {
            return NGX_ERROR;
        }
        close_src = 1;

    }

    if (src == dst) {
        return NGX_OK;
    }

    dup2(src, dst);

    if (close_src) {
        ngx_close_file(src);
    }
    return NGX_OK;

#else
    return NGX_DONE;
#endif
}