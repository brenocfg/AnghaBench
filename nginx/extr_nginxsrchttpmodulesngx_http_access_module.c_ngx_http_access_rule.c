#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_19__ {int len; char* data; } ;
typedef  TYPE_4__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {int deny; int /*<<< orphan*/  addr; int /*<<< orphan*/  mask; } ;
typedef  TYPE_5__ ngx_http_access_rule_t ;
struct TYPE_21__ {int /*<<< orphan*/ * rules; } ;
typedef  TYPE_6__ ngx_http_access_loc_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_7__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_17__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  mask; } ;
struct TYPE_18__ {TYPE_2__ in; } ;
struct TYPE_23__ {scalar_t__ family; TYPE_3__ u; } ;
typedef  TYPE_8__ ngx_cidr_t ;
struct TYPE_16__ {TYPE_4__* elts; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_8__*,int) ; 
 scalar_t__ ngx_ptocidr (TYPE_4__*,TYPE_8__*) ; 
 scalar_t__ ngx_strcmp (char*,char*) ; 

__attribute__((used)) static char *
ngx_http_access_rule(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_access_loc_conf_t *alcf = conf;

    ngx_int_t                   rc;
    ngx_uint_t                  all;
    ngx_str_t                  *value;
    ngx_cidr_t                  cidr;
    ngx_http_access_rule_t     *rule;
#if (NGX_HAVE_INET6)
    ngx_http_access_rule6_t    *rule6;
#endif
#if (NGX_HAVE_UNIX_DOMAIN)
    ngx_http_access_rule_un_t  *rule_un;
#endif

    all = 0;
    ngx_memzero(&cidr, sizeof(ngx_cidr_t));

    value = cf->args->elts;

    if (value[1].len == 3 && ngx_strcmp(value[1].data, "all") == 0) {
        all = 1;

#if (NGX_HAVE_UNIX_DOMAIN)
    } else if (value[1].len == 5 && ngx_strcmp(value[1].data, "unix:") == 0) {
        cidr.family = AF_UNIX;
#endif

    } else {
        rc = ngx_ptocidr(&value[1], &cidr);

        if (rc == NGX_ERROR) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                         "invalid parameter \"%V\"", &value[1]);
            return NGX_CONF_ERROR;
        }

        if (rc == NGX_DONE) {
            ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                         "low address bits of %V are meaningless", &value[1]);
        }
    }

    if (cidr.family == AF_INET || all) {

        if (alcf->rules == NULL) {
            alcf->rules = ngx_array_create(cf->pool, 4,
                                           sizeof(ngx_http_access_rule_t));
            if (alcf->rules == NULL) {
                return NGX_CONF_ERROR;
            }
        }

        rule = ngx_array_push(alcf->rules);
        if (rule == NULL) {
            return NGX_CONF_ERROR;
        }

        rule->mask = cidr.u.in.mask;
        rule->addr = cidr.u.in.addr;
        rule->deny = (value[0].data[0] == 'd') ? 1 : 0;
    }

#if (NGX_HAVE_INET6)
    if (cidr.family == AF_INET6 || all) {

        if (alcf->rules6 == NULL) {
            alcf->rules6 = ngx_array_create(cf->pool, 4,
                                            sizeof(ngx_http_access_rule6_t));
            if (alcf->rules6 == NULL) {
                return NGX_CONF_ERROR;
            }
        }

        rule6 = ngx_array_push(alcf->rules6);
        if (rule6 == NULL) {
            return NGX_CONF_ERROR;
        }

        rule6->mask = cidr.u.in6.mask;
        rule6->addr = cidr.u.in6.addr;
        rule6->deny = (value[0].data[0] == 'd') ? 1 : 0;
    }
#endif

#if (NGX_HAVE_UNIX_DOMAIN)
    if (cidr.family == AF_UNIX || all) {

        if (alcf->rules_un == NULL) {
            alcf->rules_un = ngx_array_create(cf->pool, 1,
                                            sizeof(ngx_http_access_rule_un_t));
            if (alcf->rules_un == NULL) {
                return NGX_CONF_ERROR;
            }
        }

        rule_un = ngx_array_push(alcf->rules_un);
        if (rule_un == NULL) {
            return NGX_CONF_ERROR;
        }

        rule_un->deny = (value[0].data[0] == 'd') ? 1 : 0;
    }
#endif

    return NGX_CONF_OK;
}