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
typedef  int /*<<< orphan*/  ngx_array_t ;

/* Variables and functions */
 void* ngx_array_push_n (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void *
ngx_http_lua_script_add_code(ngx_array_t *codes, size_t size)
{
    return ngx_array_push_n(codes, size);
}