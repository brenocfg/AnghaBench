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
typedef  scalar_t__ time_t ;
typedef  int ngx_uint_t ;
struct TYPE_8__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_9__ {size_t sbrk_size; } ;
typedef  TYPE_3__ ngx_http_degradation_main_conf_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  ngx_http_degradation_module ; 
 TYPE_3__* ngx_http_get_module_main_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ ngx_palloc ; 
 scalar_t__ ngx_time () ; 
 scalar_t__ sbrk (int /*<<< orphan*/ ) ; 

ngx_uint_t
ngx_http_degraded(ngx_http_request_t *r)
{
    time_t                             now;
    ngx_uint_t                         log;
    static size_t                      sbrk_size;
    static time_t                      sbrk_time;
    ngx_http_degradation_main_conf_t  *dmcf;

    dmcf = ngx_http_get_module_main_conf(r, ngx_http_degradation_module);

    if (dmcf->sbrk_size) {

        log = 0;
        now = ngx_time();

        /* lock mutex */

        if (now != sbrk_time) {

            /*
             * ELF/i386 is loaded at 0x08000000, 128M
             * ELF/amd64 is loaded at 0x00400000, 4M
             *
             * use a function address to subtract the loading address
             */

            sbrk_size = (size_t) sbrk(0) - ((uintptr_t) ngx_palloc & ~0x3FFFFF);
            sbrk_time = now;
            log = 1;
        }

        /* unlock mutex */

        if (sbrk_size >= dmcf->sbrk_size) {
            if (log) {
                ngx_log_error(NGX_LOG_NOTICE, r->connection->log, 0,
                              "degradation sbrk:%uzM",
                              sbrk_size / (1024 * 1024));
            }

            return 1;
        }
    }

    return 0;
}