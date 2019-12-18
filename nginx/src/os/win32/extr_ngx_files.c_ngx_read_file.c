#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_long ;
typedef  int /*<<< orphan*/  u_char ;
typedef  void* ssize_t ;
typedef  int off_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  offset; TYPE_1__ name; int /*<<< orphan*/  log; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ ngx_file_t ;
typedef  scalar_t__ ngx_err_t ;
struct TYPE_8__ {int /*<<< orphan*/ * hEvent; void* OffsetHigh; void* Offset; scalar_t__ InternalHigh; scalar_t__ Internal; } ;
typedef  TYPE_3__ OVERLAPPED ;

/* Variables and functions */
 scalar_t__ ERROR_HANDLE_EOF ; 
 void* NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,void**,TYPE_3__*) ; 
 scalar_t__ ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 

ssize_t
ngx_read_file(ngx_file_t *file, u_char *buf, size_t size, off_t offset)
{
    u_long      n;
    ngx_err_t   err;
    OVERLAPPED  ovlp, *povlp;

    ovlp.Internal = 0;
    ovlp.InternalHigh = 0;
    ovlp.Offset = (u_long) offset;
    ovlp.OffsetHigh = (u_long) (offset >> 32);
    ovlp.hEvent = NULL;

    povlp = &ovlp;

    if (ReadFile(file->fd, buf, size, &n, povlp) == 0) {
        err = ngx_errno;

        if (err == ERROR_HANDLE_EOF) {
            return 0;
        }

        ngx_log_error(NGX_LOG_ERR, file->log, err,
                      "ReadFile() \"%s\" failed", file->name.data);
        return NGX_ERROR;
    }

    file->offset += n;

    return n;
}