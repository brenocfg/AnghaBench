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
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_3__ {int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ ngx_dir_t ;

/* Variables and functions */
 scalar_t__ FindClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 

ngx_int_t
ngx_close_dir(ngx_dir_t *dir)
{
    if (FindClose(dir->dir) == 0) {
        return NGX_ERROR;
    }

    return NGX_OK;
}