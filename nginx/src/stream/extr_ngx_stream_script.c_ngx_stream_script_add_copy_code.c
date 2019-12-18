#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_7__ {size_t len; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ ngx_stream_script_copy_code_t ;
struct TYPE_8__ {int /*<<< orphan*/  zero; int /*<<< orphan*/  main; int /*<<< orphan*/ * values; int /*<<< orphan*/ * lengths; } ;
typedef  TYPE_2__ ngx_stream_script_compile_t ;
typedef  int /*<<< orphan*/  ngx_stream_script_code_pt ;
struct TYPE_9__ {size_t len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 char* ngx_cpymem (char*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* ngx_stream_script_add_code (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_stream_script_copy_code ; 
 scalar_t__ ngx_stream_script_copy_len_code ; 

__attribute__((used)) static ngx_int_t
ngx_stream_script_add_copy_code(ngx_stream_script_compile_t *sc,
    ngx_str_t *value, ngx_uint_t last)
{
    u_char                         *p;
    size_t                          size, len, zero;
    ngx_stream_script_copy_code_t  *code;

    zero = (sc->zero && last);
    len = value->len + zero;

    code = ngx_stream_script_add_code(*sc->lengths,
                                      sizeof(ngx_stream_script_copy_code_t),
                                      NULL);
    if (code == NULL) {
        return NGX_ERROR;
    }

    code->code = (ngx_stream_script_code_pt) (void *)
                                               ngx_stream_script_copy_len_code;
    code->len = len;

    size = (sizeof(ngx_stream_script_copy_code_t) + len + sizeof(uintptr_t) - 1)
            & ~(sizeof(uintptr_t) - 1);

    code = ngx_stream_script_add_code(*sc->values, size, &sc->main);
    if (code == NULL) {
        return NGX_ERROR;
    }

    code->code = ngx_stream_script_copy_code;
    code->len = len;

    p = ngx_cpymem((u_char *) code + sizeof(ngx_stream_script_copy_code_t),
                   value->data, value->len);

    if (zero) {
        *p = '\0';
        sc->zero = 0;
    }

    return NGX_OK;
}