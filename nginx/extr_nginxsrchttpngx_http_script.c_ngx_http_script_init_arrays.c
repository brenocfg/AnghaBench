#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_script_var_code_t ;
typedef  int /*<<< orphan*/  ngx_http_script_copy_code_t ;
struct TYPE_7__ {int variables; int /*<<< orphan*/ ** values; TYPE_2__* cf; TYPE_1__* source; int /*<<< orphan*/ ** lengths; int /*<<< orphan*/ ** flushes; } ;
typedef  TYPE_3__ ngx_http_script_compile_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;
struct TYPE_5__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 void* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_script_init_arrays(ngx_http_script_compile_t *sc)
{
    ngx_uint_t   n;

    if (sc->flushes && *sc->flushes == NULL) {
        n = sc->variables ? sc->variables : 1;
        *sc->flushes = ngx_array_create(sc->cf->pool, n, sizeof(ngx_uint_t));
        if (*sc->flushes == NULL) {
            return NGX_ERROR;
        }
    }

    if (*sc->lengths == NULL) {
        n = sc->variables * (2 * sizeof(ngx_http_script_copy_code_t)
                             + sizeof(ngx_http_script_var_code_t))
            + sizeof(uintptr_t);

        *sc->lengths = ngx_array_create(sc->cf->pool, n, 1);
        if (*sc->lengths == NULL) {
            return NGX_ERROR;
        }
    }

    if (*sc->values == NULL) {
        n = (sc->variables * (2 * sizeof(ngx_http_script_copy_code_t)
                              + sizeof(ngx_http_script_var_code_t))
                + sizeof(uintptr_t)
                + sc->source->len
                + sizeof(uintptr_t) - 1)
            & ~(sizeof(uintptr_t) - 1);

        *sc->values = ngx_array_create(sc->cf->pool, n, 1);
        if (*sc->values == NULL) {
            return NGX_ERROR;
        }
    }

    sc->variables = 0;

    return NGX_OK;
}