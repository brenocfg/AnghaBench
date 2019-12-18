#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_12__ {TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_13__ {int mask; int addr; size_t flags; int /*<<< orphan*/  deny; } ;
typedef  TYPE_4__ ngx_rtmp_access_rule_t ;
struct TYPE_10__ {size_t nelts; TYPE_4__* elts; } ;
struct TYPE_14__ {TYPE_1__ rules; } ;
typedef  TYPE_5__ ngx_rtmp_access_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int in_addr_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  ngx_rtmp_access_found (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_access_module ; 
 TYPE_5__* ngx_rtmp_get_module_app_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_access_inet(ngx_rtmp_session_t *s, in_addr_t addr, ngx_uint_t flag)
{
    ngx_uint_t                  i;
    ngx_rtmp_access_rule_t     *rule;
    ngx_rtmp_access_app_conf_t *ascf;

    ascf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_access_module);

    rule = ascf->rules.elts;
    for (i = 0; i < ascf->rules.nelts; i++) {

        ngx_log_debug3(NGX_LOG_DEBUG_HTTP, s->connection->log, 0,
                       "access: %08XD %08XD %08XD",
                       addr, rule[i].mask, rule[i].addr);

        if ((addr & rule[i].mask) == rule[i].addr && (flag & rule[i].flags)) {
            return ngx_rtmp_access_found(s, rule[i].deny);
        }
    }

    return NGX_OK;
}