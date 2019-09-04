#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_8__ {scalar_t__ (* init_upstream ) (int /*<<< orphan*/ *,TYPE_3__*) ;} ;
struct TYPE_9__ {TYPE_2__ peer; } ;
typedef  TYPE_3__ ngx_stream_upstream_srv_conf_t ;
struct TYPE_7__ {size_t nelts; TYPE_3__** elts; } ;
struct TYPE_10__ {TYPE_1__ upstreams; } ;
typedef  TYPE_4__ ngx_stream_upstream_main_conf_t ;
typedef  scalar_t__ (* ngx_stream_upstream_init_pt ) (int /*<<< orphan*/ *,TYPE_3__*) ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_stream_upstream_init_round_robin (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static char *
ngx_stream_upstream_init_main_conf(ngx_conf_t *cf, void *conf)
{
    ngx_stream_upstream_main_conf_t *umcf = conf;

    ngx_uint_t                        i;
    ngx_stream_upstream_init_pt       init;
    ngx_stream_upstream_srv_conf_t  **uscfp;

    uscfp = umcf->upstreams.elts;

    for (i = 0; i < umcf->upstreams.nelts; i++) {

        init = uscfp[i]->peer.init_upstream
                                         ? uscfp[i]->peer.init_upstream
                                         : ngx_stream_upstream_init_round_robin;

        if (init(cf, uscfp[i]) != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}