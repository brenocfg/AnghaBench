#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {int len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {scalar_t__ cFileName; } ;
struct TYPE_7__ {int last; int /*<<< orphan*/  pattern; int /*<<< orphan*/  log; TYPE_1__ name; TYPE_5__ finddata; int /*<<< orphan*/  dir; scalar_t__ ready; scalar_t__ no_match; } ;
typedef  TYPE_2__ ngx_glob_t ;
typedef  scalar_t__ ngx_err_t ;

/* Variables and functions */
 scalar_t__ FindNextFile (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  NGX_DONE ; 
 scalar_t__ NGX_ENOMOREFILES ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_cpystrn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ngx_errno ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t ngx_strlen (scalar_t__) ; 

ngx_int_t
ngx_read_glob(ngx_glob_t *gl, ngx_str_t *name)
{
    size_t     len;
    ngx_err_t  err;

    if (gl->no_match) {
        return NGX_DONE;
    }

    if (gl->ready) {
        *name = gl->name;

        gl->ready = 0;
        return NGX_OK;
    }

    ngx_free(gl->name.data);
    gl->name.data = NULL;

    if (FindNextFile(gl->dir, &gl->finddata) != 0) {

        len = ngx_strlen(gl->finddata.cFileName);
        gl->name.len = gl->last + len;

        gl->name.data = ngx_alloc(gl->name.len + 1, gl->log);
        if (gl->name.data == NULL) {
            return NGX_ERROR;
        }

        ngx_memcpy(gl->name.data, gl->pattern, gl->last);
        ngx_cpystrn(gl->name.data + gl->last, (u_char *) gl->finddata.cFileName,
                    len + 1);

        *name = gl->name;

        return NGX_OK;
    }

    err = ngx_errno;

    if (err == NGX_ENOMOREFILES) {
        return NGX_DONE;
    }

    ngx_log_error(NGX_LOG_ALERT, gl->log, err,
                  "FindNextFile(%s) failed", gl->pattern);

    return NGX_ERROR;
}