#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_2__ {size_t index; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ NGX_MAX_DYNAMIC_MODULES ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_max_module ; 
 int /*<<< orphan*/ * ngx_module_names ; 
 TYPE_1__** ngx_modules ; 
 size_t ngx_modules_n ; 

ngx_int_t
ngx_preinit_modules(void)
{
    ngx_uint_t  i;

    for (i = 0; ngx_modules[i]; i++) {
        ngx_modules[i]->index = i;
        ngx_modules[i]->name = ngx_module_names[i];
    }

    ngx_modules_n = i;
    ngx_max_module = ngx_modules_n + NGX_MAX_DYNAMIC_MODULES;

    return NGX_OK;
}