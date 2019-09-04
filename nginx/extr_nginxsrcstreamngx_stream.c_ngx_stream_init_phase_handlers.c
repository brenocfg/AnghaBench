#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_13__ {size_t next; int /*<<< orphan*/  handler; int /*<<< orphan*/  checker; } ;
typedef  TYPE_4__ ngx_stream_phase_handler_t ;
typedef  int /*<<< orphan*/  ngx_stream_phase_handler_pt ;
typedef  int /*<<< orphan*/  ngx_stream_handler_pt ;
struct TYPE_10__ {TYPE_4__* handlers; } ;
struct TYPE_14__ {TYPE_3__* phases; TYPE_1__ phase_engine; } ;
typedef  TYPE_5__ ngx_stream_core_main_conf_t ;
typedef  size_t ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_11__ {size_t nelts; int /*<<< orphan*/ * elts; } ;
struct TYPE_12__ {TYPE_2__ handlers; } ;

/* Variables and functions */
 size_t NGX_ERROR ; 
 size_t NGX_OK ; 
#define  NGX_STREAM_CONTENT_PHASE 129 
 size_t NGX_STREAM_LOG_PHASE ; 
#define  NGX_STREAM_PREREAD_PHASE 128 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_stream_core_content_phase ; 
 int /*<<< orphan*/  ngx_stream_core_generic_phase ; 
 int /*<<< orphan*/  ngx_stream_core_preread_phase ; 

__attribute__((used)) static ngx_int_t
ngx_stream_init_phase_handlers(ngx_conf_t *cf,
    ngx_stream_core_main_conf_t *cmcf)
{
    ngx_int_t                     j;
    ngx_uint_t                    i, n;
    ngx_stream_handler_pt        *h;
    ngx_stream_phase_handler_t   *ph;
    ngx_stream_phase_handler_pt   checker;

    n = 1 /* content phase */;

    for (i = 0; i < NGX_STREAM_LOG_PHASE; i++) {
        n += cmcf->phases[i].handlers.nelts;
    }

    ph = ngx_pcalloc(cf->pool,
                     n * sizeof(ngx_stream_phase_handler_t) + sizeof(void *));
    if (ph == NULL) {
        return NGX_ERROR;
    }

    cmcf->phase_engine.handlers = ph;
    n = 0;

    for (i = 0; i < NGX_STREAM_LOG_PHASE; i++) {
        h = cmcf->phases[i].handlers.elts;

        switch (i) {

        case NGX_STREAM_PREREAD_PHASE:
            checker = ngx_stream_core_preread_phase;
            break;

        case NGX_STREAM_CONTENT_PHASE:
            ph->checker = ngx_stream_core_content_phase;
            n++;
            ph++;

            continue;

        default:
            checker = ngx_stream_core_generic_phase;
        }

        n += cmcf->phases[i].handlers.nelts;

        for (j = cmcf->phases[i].handlers.nelts - 1; j >= 0; j--) {
            ph->checker = checker;
            ph->handler = h[j];
            ph->next = n;
            ph++;
        }
    }

    return NGX_OK;
}