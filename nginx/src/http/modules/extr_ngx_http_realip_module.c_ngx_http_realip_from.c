#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_31__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_6__ sin_addr; } ;
struct TYPE_32__ {int mask; int /*<<< orphan*/  addr; } ;
struct TYPE_27__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_28__ {TYPE_2__ mask; int /*<<< orphan*/  addr; } ;
struct TYPE_33__ {TYPE_7__ in; TYPE_3__ in6; } ;
struct TYPE_23__ {int /*<<< orphan*/  data; } ;
struct TYPE_34__ {int family; int naddrs; TYPE_8__ u; TYPE_5__* addrs; TYPE_10__ host; int /*<<< orphan*/  err; } ;
typedef  TYPE_9__ ngx_url_t ;
typedef  size_t ngx_uint_t ;
typedef  TYPE_10__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_24__ {int /*<<< orphan*/ * from; } ;
typedef  TYPE_11__ ngx_http_realip_loc_conf_t ;
struct TYPE_25__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_12__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
typedef  TYPE_9__ ngx_cidr_t ;
struct TYPE_30__ {TYPE_4__* sockaddr; } ;
struct TYPE_29__ {int sa_family; } ;
struct TYPE_26__ {TYPE_10__* elts; } ;

/* Variables and functions */
#define  AF_INET6 128 
 int AF_UNIX ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_9__* ngx_array_push (int /*<<< orphan*/ *) ; 
 TYPE_9__* ngx_array_push_n (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ,char*,TYPE_10__*,...) ; 
 scalar_t__ ngx_inet_resolve_host (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_9__*,int) ; 
 scalar_t__ ngx_ptocidr (TYPE_10__*,TYPE_9__*) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
ngx_http_realip_from(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_realip_loc_conf_t *rlcf = conf;

    ngx_int_t             rc;
    ngx_str_t            *value;
    ngx_url_t             u;
    ngx_cidr_t            c, *cidr;
    ngx_uint_t            i;
    struct sockaddr_in   *sin;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6  *sin6;
#endif

    value = cf->args->elts;

    if (rlcf->from == NULL) {
        rlcf->from = ngx_array_create(cf->pool, 2,
                                      sizeof(ngx_cidr_t));
        if (rlcf->from == NULL) {
            return NGX_CONF_ERROR;
        }
    }

#if (NGX_HAVE_UNIX_DOMAIN)

    if (ngx_strcmp(value[1].data, "unix:") == 0) {
        cidr = ngx_array_push(rlcf->from);
        if (cidr == NULL) {
            return NGX_CONF_ERROR;
        }

        cidr->family = AF_UNIX;
        return NGX_CONF_OK;
    }

#endif

    rc = ngx_ptocidr(&value[1], &c);

    if (rc != NGX_ERROR) {
        if (rc == NGX_DONE) {
            ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                               "low address bits of %V are meaningless",
                               &value[1]);
        }

        cidr = ngx_array_push(rlcf->from);
        if (cidr == NULL) {
            return NGX_CONF_ERROR;
        }

        *cidr = c;

        return NGX_CONF_OK;
    }

    ngx_memzero(&u, sizeof(ngx_url_t));
    u.host = value[1];

    if (ngx_inet_resolve_host(cf->pool, &u) != NGX_OK) {
        if (u.err) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "%s in set_real_ip_from \"%V\"",
                               u.err, &u.host);
        }

        return NGX_CONF_ERROR;
    }

    cidr = ngx_array_push_n(rlcf->from, u.naddrs);
    if (cidr == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_memzero(cidr, u.naddrs * sizeof(ngx_cidr_t));

    for (i = 0; i < u.naddrs; i++) {
        cidr[i].family = u.addrs[i].sockaddr->sa_family;

        switch (cidr[i].family) {

#if (NGX_HAVE_INET6)
        case AF_INET6:
            sin6 = (struct sockaddr_in6 *) u.addrs[i].sockaddr;
            cidr[i].u.in6.addr = sin6->sin6_addr;
            ngx_memset(cidr[i].u.in6.mask.s6_addr, 0xff, 16);
            break;
#endif

        default: /* AF_INET */
            sin = (struct sockaddr_in *) u.addrs[i].sockaddr;
            cidr[i].u.in.addr = sin->sin_addr.s_addr;
            cidr[i].u.in.mask = 0xffffffff;
            break;
        }
    }

    return NGX_CONF_OK;
}