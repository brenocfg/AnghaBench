#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int NGX_ERROR ; 

int
ngx_http_lua_ffi_master_pid(void)
{
#if (nginx_version >= 1013008)
    if (ngx_process == NGX_PROCESS_SINGLE) {
        return (int) ngx_pid;
    }

    return (int) ngx_parent;
#else
    return NGX_ERROR;
#endif
}