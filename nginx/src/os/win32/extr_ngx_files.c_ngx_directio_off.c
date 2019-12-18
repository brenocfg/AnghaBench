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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_fd_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_FILE_ERROR ; 

ngx_int_t
ngx_directio_off(ngx_fd_t fd)
{
    return ~NGX_FILE_ERROR;
}