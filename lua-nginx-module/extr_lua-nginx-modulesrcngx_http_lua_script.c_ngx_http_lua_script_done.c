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
struct TYPE_3__ {int /*<<< orphan*/ * values; scalar_t__ complete_values; int /*<<< orphan*/ * lengths; scalar_t__ complete_lengths; } ;
typedef  TYPE_1__ ngx_http_lua_script_compile_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 uintptr_t* ngx_http_lua_script_add_code (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_script_done(ngx_http_lua_script_compile_t *sc)
{
    uintptr_t   *code;

    if (sc->complete_lengths) {
        code = ngx_http_lua_script_add_code(*sc->lengths, sizeof(uintptr_t));
        if (code == NULL) {
            return NGX_ERROR;
        }

        *code = (uintptr_t) NULL;
    }

    if (sc->complete_values) {
        code = ngx_http_lua_script_add_code(*sc->values, sizeof(uintptr_t));
        if (code == NULL) {
            return NGX_ERROR;
        }

        *code = (uintptr_t) NULL;
    }

    return NGX_OK;
}