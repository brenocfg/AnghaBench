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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int time_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_fd_t ;
struct TYPE_3__ {void* dwHighDateTime; void* dwLowDateTime; } ;
typedef  TYPE_1__ FILETIME ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ SetFileTime (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

ngx_int_t
ngx_set_file_time(u_char *name, ngx_fd_t fd, time_t s)
{
    uint64_t  intervals;
    FILETIME  ft;

    /* 116444736000000000 is commented in src/os/win32/ngx_time.c */

    intervals = s * 10000000 + 116444736000000000;

    ft.dwLowDateTime = (DWORD) intervals;
    ft.dwHighDateTime = (DWORD) (intervals >> 32);

    if (SetFileTime(fd, NULL, NULL, &ft) != 0) {
        return NGX_OK;
    }

    return NGX_ERROR;
}