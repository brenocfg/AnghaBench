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
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_5__ {uintptr_t index; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ ngx_http_script_var_code_t ;
struct TYPE_6__ {int /*<<< orphan*/  main; int /*<<< orphan*/ * values; int /*<<< orphan*/ * lengths; int /*<<< orphan*/ * flushes; int /*<<< orphan*/  cf; } ;
typedef  TYPE_2__ ngx_http_script_compile_t ;
typedef  int /*<<< orphan*/  ngx_http_script_code_pt ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__* ngx_array_push (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_get_variable_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* ngx_http_script_add_code (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_script_copy_var_code ; 
 scalar_t__ ngx_http_script_copy_var_len_code ; 

__attribute__((used)) static ngx_int_t
ngx_http_script_add_var_code(ngx_http_script_compile_t *sc, ngx_str_t *name)
{
    ngx_int_t                    index, *p;
    ngx_http_script_var_code_t  *code;

    index = ngx_http_get_variable_index(sc->cf, name);

    if (index == NGX_ERROR) {
        return NGX_ERROR;
    }

    if (sc->flushes) {
        p = ngx_array_push(*sc->flushes);
        if (p == NULL) {
            return NGX_ERROR;
        }

        *p = index;
    }

    code = ngx_http_script_add_code(*sc->lengths,
                                    sizeof(ngx_http_script_var_code_t), NULL);
    if (code == NULL) {
        return NGX_ERROR;
    }

    code->code = (ngx_http_script_code_pt) (void *)
                                             ngx_http_script_copy_var_len_code;
    code->index = (uintptr_t) index;

    code = ngx_http_script_add_code(*sc->values,
                                    sizeof(ngx_http_script_var_code_t),
                                    &sc->main);
    if (code == NULL) {
        return NGX_ERROR;
    }

    code->code = ngx_http_script_copy_var_code;
    code->index = (uintptr_t) index;

    return NGX_OK;
}