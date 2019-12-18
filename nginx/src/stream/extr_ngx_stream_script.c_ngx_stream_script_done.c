#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {int /*<<< orphan*/  main; int /*<<< orphan*/ * values; scalar_t__ complete_values; int /*<<< orphan*/ * lengths; scalar_t__ complete_lengths; scalar_t__ root_prefix; scalar_t__ conf_prefix; scalar_t__ zero; } ;
typedef  TYPE_1__ ngx_stream_script_compile_t ;
struct TYPE_8__ {int len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 uintptr_t* ngx_stream_script_add_code (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_stream_script_add_copy_code (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_stream_script_add_full_name_code (TYPE_1__*) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_script_done(ngx_stream_script_compile_t *sc)
{
    ngx_str_t    zero;
    uintptr_t   *code;

    if (sc->zero) {

        zero.len = 1;
        zero.data = (u_char *) "\0";

        if (ngx_stream_script_add_copy_code(sc, &zero, 0) != NGX_OK) {
            return NGX_ERROR;
        }
    }

    if (sc->conf_prefix || sc->root_prefix) {
        if (ngx_stream_script_add_full_name_code(sc) != NGX_OK) {
            return NGX_ERROR;
        }
    }

    if (sc->complete_lengths) {
        code = ngx_stream_script_add_code(*sc->lengths, sizeof(uintptr_t),
                                          NULL);
        if (code == NULL) {
            return NGX_ERROR;
        }

        *code = (uintptr_t) NULL;
    }

    if (sc->complete_values) {
        code = ngx_stream_script_add_code(*sc->values, sizeof(uintptr_t),
                                          &sc->main);
        if (code == NULL) {
            return NGX_ERROR;
        }

        *code = (uintptr_t) NULL;
    }

    return NGX_OK;
}