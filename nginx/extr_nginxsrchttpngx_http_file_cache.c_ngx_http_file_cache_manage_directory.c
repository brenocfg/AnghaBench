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
typedef  int /*<<< orphan*/  ngx_tree_ctx_t ;
struct TYPE_3__ {int len; scalar_t__ data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_file_cache_manage_directory(ngx_tree_ctx_t *ctx, ngx_str_t *path)
{
    if (path->len >= 5
        && ngx_strncmp(path->data + path->len - 5, "/temp", 5) == 0)
    {
        return NGX_DECLINED;
    }

    return NGX_OK;
}