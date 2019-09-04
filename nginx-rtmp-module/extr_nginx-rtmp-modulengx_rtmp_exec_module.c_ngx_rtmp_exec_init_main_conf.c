#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_11__ {int managed; int respawn_timeout; scalar_t__ kill_signal; int /*<<< orphan*/ * log; int /*<<< orphan*/ * conf; } ;
typedef  TYPE_3__ ngx_rtmp_exec_t ;
struct TYPE_10__ {scalar_t__ nelts; int /*<<< orphan*/ * elts; } ;
struct TYPE_12__ {int respawn_timeout; scalar_t__ kill_signal; int /*<<< orphan*/ * log; TYPE_2__ static_conf; int /*<<< orphan*/  static_exec; } ;
typedef  TYPE_4__ ngx_rtmp_exec_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_exec_conf_t ;
struct TYPE_13__ {TYPE_1__* cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_conf_t ;
struct TYPE_9__ {int /*<<< orphan*/  new_log; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET ; 
 int NGX_CONF_UNSET_MSEC ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ SIGKILL ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 TYPE_3__* ngx_array_push_n (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 

__attribute__((used)) static char *
ngx_rtmp_exec_init_main_conf(ngx_conf_t *cf, void *conf)
{
    ngx_rtmp_exec_main_conf_t  *emcf = conf;
    ngx_rtmp_exec_conf_t       *ec;
    ngx_rtmp_exec_t            *e;
    ngx_uint_t                  n;

    if (emcf->respawn_timeout == NGX_CONF_UNSET_MSEC) {
        emcf->respawn_timeout = 5000;
    }

#if !(NGX_WIN32)
    if (emcf->kill_signal == NGX_CONF_UNSET) {
        emcf->kill_signal = SIGKILL;
    }
#endif

    if (ngx_array_init(&emcf->static_exec, cf->pool,
                       emcf->static_conf.nelts,
                       sizeof(ngx_rtmp_exec_t)) != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    e = ngx_array_push_n(&emcf->static_exec, emcf->static_conf.nelts);
    if (e == NULL) {
        return NGX_CONF_ERROR;
    }

    emcf->log = &cf->cycle->new_log;

    ec = emcf->static_conf.elts;

    for (n = 0; n < emcf->static_conf.nelts; n++, e++, ec++) {
        ngx_memzero(e, sizeof(*e));
        e->conf = ec;
        e->managed = 1;
        e->log = emcf->log;
        e->respawn_timeout = emcf->respawn_timeout;
        e->kill_signal = emcf->kill_signal;
    }

    return NGX_CONF_OK;
}