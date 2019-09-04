#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_char ;
typedef  long ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/  nFileSizeLow; int /*<<< orphan*/  nFileSizeHigh; int /*<<< orphan*/  ftLastWriteTime; int /*<<< orphan*/  ftLastAccessTime; int /*<<< orphan*/  ftCreationTime; int /*<<< orphan*/  dwFileAttributes; } ;
typedef  TYPE_1__ ngx_file_info_t ;
typedef  int /*<<< orphan*/  ngx_err_t ;
struct TYPE_6__ {int /*<<< orphan*/  nFileSizeLow; int /*<<< orphan*/  nFileSizeHigh; int /*<<< orphan*/  ftLastWriteTime; int /*<<< orphan*/  ftLastAccessTime; int /*<<< orphan*/  ftCreationTime; int /*<<< orphan*/  dwFileAttributes; } ;
typedef  TYPE_2__ WIN32_FILE_ATTRIBUTE_DATA ;

/* Variables and functions */
 long GetFileAttributesExW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetFileExInfoStandard ; 
 long NGX_FILE_ERROR ; 
 scalar_t__ NGX_OK ; 
 int NGX_UTF16_BUFLEN ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_set_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_utf8_to_utf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ ngx_win32_check_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

ngx_int_t
ngx_file_info(u_char *file, ngx_file_info_t *sb)
{
    size_t                      len;
    long                        rc;
    u_short                    *u;
    ngx_err_t                   err;
    WIN32_FILE_ATTRIBUTE_DATA   fa;
    u_short                     utf16[NGX_UTF16_BUFLEN];

    len = NGX_UTF16_BUFLEN;

    u = ngx_utf8_to_utf16(utf16, file, &len);

    if (u == NULL) {
        return NGX_FILE_ERROR;
    }

    rc = NGX_FILE_ERROR;

    if (ngx_win32_check_filename(file, u, len) != NGX_OK) {
        goto failed;
    }

    rc = GetFileAttributesExW(u, GetFileExInfoStandard, &fa);

    sb->dwFileAttributes = fa.dwFileAttributes;
    sb->ftCreationTime = fa.ftCreationTime;
    sb->ftLastAccessTime = fa.ftLastAccessTime;
    sb->ftLastWriteTime = fa.ftLastWriteTime;
    sb->nFileSizeHigh = fa.nFileSizeHigh;
    sb->nFileSizeLow = fa.nFileSizeLow;

failed:

    if (u != utf16) {
        err = ngx_errno;
        ngx_free(u);
        ngx_set_errno(err);
    }

    return rc;
}