#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_20__ {int len; char* data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_21__ {int deny; int flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  mask; } ;
typedef  TYPE_5__ ngx_rtmp_access_rule_t ;
struct TYPE_22__ {int /*<<< orphan*/  rules; } ;
typedef  TYPE_6__ ngx_rtmp_access_app_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; TYPE_1__* args; } ;
typedef  TYPE_7__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_18__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  mask; } ;
struct TYPE_19__ {TYPE_2__ in; } ;
struct TYPE_24__ {int family; TYPE_3__ u; } ;
typedef  TYPE_8__ ngx_cidr_t ;
struct TYPE_17__ {int nelts; TYPE_4__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int NGX_RTMP_ACCESS_PLAY ; 
 int NGX_RTMP_ACCESS_PUBLISH ; 
 TYPE_5__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_8__*,int) ; 
 scalar_t__ ngx_ptocidr (TYPE_4__*,TYPE_8__*) ; 
 scalar_t__ ngx_strcmp (char*,char*) ; 

__attribute__((used)) static char *
ngx_rtmp_access_rule(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_rtmp_access_app_conf_t         *ascf = conf;

    ngx_int_t                           rc;
    ngx_uint_t                          all;
    ngx_str_t                          *value;
    ngx_cidr_t                          cidr;
    ngx_rtmp_access_rule_t             *rule;
#if (NGX_HAVE_INET6)
    ngx_rtmp_access_rule6_t            *rule6;
#endif
    size_t                              n;
    ngx_uint_t                          flags;

    ngx_memzero(&cidr, sizeof(ngx_cidr_t));

    value = cf->args->elts;

    n = 1;
    flags = 0;

    if (cf->args->nelts == 2) {

        flags = NGX_RTMP_ACCESS_PUBLISH | NGX_RTMP_ACCESS_PLAY;

    } else {

        for(; n < cf->args->nelts - 1; ++n) {

            if (value[n].len == sizeof("publish") - 1 &&
                ngx_strcmp(value[1].data, "publish") == 0)
            {
                flags |= NGX_RTMP_ACCESS_PUBLISH;
                continue;

            }

            if (value[n].len == sizeof("play") - 1 &&
                ngx_strcmp(value[1].data, "play") == 0)
            {
                flags |= NGX_RTMP_ACCESS_PLAY;
                continue;

            }

            ngx_log_error(NGX_LOG_ERR, cf->log, 0,
                          "unexpected access specified: '%V'", &value[n]);
            return NGX_CONF_ERROR;
        }
    }

    all = (value[n].len == 3 && ngx_strcmp(value[n].data, "all") == 0);

    if (!all) {

        rc = ngx_ptocidr(&value[n], &cidr);

        if (rc == NGX_ERROR) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid parameter \"%V\"", &value[1]);
            return NGX_CONF_ERROR;
        }

        if (rc == NGX_DONE) {
            ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                               "low address bits of %V are meaningless",
                               &value[1]);
        }
    }

    switch (cidr.family) {

#if (NGX_HAVE_INET6)
    case AF_INET6:
    case 0: /* all */

        rule6 = ngx_array_push(&ascf->rules6);
        if (rule6 == NULL) {
            return NGX_CONF_ERROR;
        }

        rule6->mask = cidr.u.in6.mask;
        rule6->addr = cidr.u.in6.addr;
        rule6->deny = (value[0].data[0] == 'd') ? 1 : 0;
        rule6->flags = flags;

        if (!all) {
            break;
        }

#endif
        /* fall through */

    default: /* AF_INET */

        rule = ngx_array_push(&ascf->rules);
        if (rule == NULL) {
            return NGX_CONF_ERROR;
        }

        rule->mask = cidr.u.in.mask;
        rule->addr = cidr.u.in.addr;
        rule->deny = (value[0].data[0] == 'd') ? 1 : 0;
        rule->flags = flags;
    }

    return NGX_CONF_OK;
}