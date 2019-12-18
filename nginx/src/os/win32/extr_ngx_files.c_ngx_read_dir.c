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
struct TYPE_3__ {int type; int /*<<< orphan*/  finddata; int /*<<< orphan*/  dir; scalar_t__ ready; } ;
typedef  TYPE_1__ ngx_dir_t ;

/* Variables and functions */
 scalar_t__ FindNextFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 

ngx_int_t
ngx_read_dir(ngx_dir_t *dir)
{
    if (dir->ready) {
        dir->ready = 0;
        return NGX_OK;
    }

    if (FindNextFile(dir->dir, &dir->finddata) != 0) {
        dir->type = 1;
        return NGX_OK;
    }

    return NGX_ERROR;
}