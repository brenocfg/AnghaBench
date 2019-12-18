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
typedef  size_t ngx_uint_t ;
struct TYPE_8__ {scalar_t__ worker; int /*<<< orphan*/  reuseport; } ;
typedef  TYPE_2__ ngx_listening_t ;
struct TYPE_7__ {scalar_t__ nelts; TYPE_2__* elts; } ;
struct TYPE_9__ {scalar_t__ connection_n; TYPE_1__ listening; int /*<<< orphan*/  log; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_3__ ngx_cycle_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_clone_listening (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_events_module ; 
 int /*<<< orphan*/ * ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static char *
ngx_event_init_conf(ngx_cycle_t *cycle, void *conf)
{
#if (NGX_HAVE_REUSEPORT)
    ngx_uint_t        i;
    ngx_listening_t  *ls;
#endif

    if (ngx_get_conf(cycle->conf_ctx, ngx_events_module) == NULL) {
        ngx_log_error(NGX_LOG_EMERG, cycle->log, 0,
                      "no \"events\" section in configuration");
        return NGX_CONF_ERROR;
    }

    if (cycle->connection_n < cycle->listening.nelts + 1) {

        /*
         * there should be at least one connection for each listening
         * socket, plus an additional connection for channel
         */

        ngx_log_error(NGX_LOG_EMERG, cycle->log, 0,
                      "%ui worker_connections are not enough "
                      "for %ui listening sockets",
                      cycle->connection_n, cycle->listening.nelts);

        return NGX_CONF_ERROR;
    }

#if (NGX_HAVE_REUSEPORT)

    ls = cycle->listening.elts;
    for (i = 0; i < cycle->listening.nelts; i++) {

        if (!ls[i].reuseport || ls[i].worker != 0) {
            continue;
        }

        if (ngx_clone_listening(cycle, &ls[i]) != NGX_OK) {
            return NGX_CONF_ERROR;
        }

        /* cloning may change cycle->listening.elts */

        ls = cycle->listening.elts;
    }

#endif

    return NGX_CONF_OK;
}