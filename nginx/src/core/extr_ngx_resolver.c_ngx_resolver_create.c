#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_19__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_26__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct TYPE_25__ {int default_port; int naddrs; TYPE_6__* resolver; TYPE_1__* addrs; int /*<<< orphan*/  server; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; TYPE_5__ url; int /*<<< orphan*/  err; } ;
typedef  TYPE_4__ ngx_url_t ;
typedef  size_t ngx_uint_t ;
typedef  TYPE_5__ ngx_str_t ;
struct TYPE_21__ {scalar_t__ nelts; } ;
struct TYPE_27__ {int ipv6; int ident; int resend_timeout; int tcp_timeout; int expire; scalar_t__ valid; TYPE_19__ connections; int /*<<< orphan*/  log_level; int /*<<< orphan*/ * log; TYPE_2__* event; int /*<<< orphan*/  addr6_expire_queue; int /*<<< orphan*/  addr6_resend_queue; int /*<<< orphan*/  addr6_sentinel; int /*<<< orphan*/  addr6_rbtree; int /*<<< orphan*/  addr_expire_queue; int /*<<< orphan*/  srv_expire_queue; int /*<<< orphan*/  name_expire_queue; int /*<<< orphan*/  addr_resend_queue; int /*<<< orphan*/  srv_resend_queue; int /*<<< orphan*/  name_resend_queue; int /*<<< orphan*/  addr_sentinel; int /*<<< orphan*/  addr_rbtree; int /*<<< orphan*/  srv_sentinel; int /*<<< orphan*/  srv_rbtree; int /*<<< orphan*/  name_sentinel; int /*<<< orphan*/  name_rbtree; } ;
typedef  TYPE_6__ ngx_resolver_t ;
typedef  TYPE_4__ ngx_resolver_connection_t ;
struct TYPE_28__ {TYPE_6__* data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_8__ ngx_pool_cleanup_t ;
typedef  int /*<<< orphan*/  ngx_event_t ;
struct TYPE_29__ {int /*<<< orphan*/  pool; TYPE_3__* cycle; } ;
typedef  TYPE_9__ ngx_conf_t ;
struct TYPE_24__ {int /*<<< orphan*/  new_log; } ;
struct TYPE_23__ {int cancelable; int /*<<< orphan*/ * log; TYPE_6__* data; int /*<<< orphan*/  handler; } ;
struct TYPE_22__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_19__*,int /*<<< orphan*/ ,size_t,int) ; 
 TYPE_4__* ngx_array_push_n (TYPE_19__*,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 
 scalar_t__ ngx_parse_time (TYPE_5__*,int) ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_4__*) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_8__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rbtree_insert_value ; 
 int /*<<< orphan*/  ngx_resolver_cleanup ; 
 int /*<<< orphan*/  ngx_resolver_rbtree_insert_addr6_value ; 
 int /*<<< orphan*/  ngx_resolver_rbtree_insert_value ; 
 int /*<<< orphan*/  ngx_resolver_resend_handler ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ *,char*,int) ; 

ngx_resolver_t *
ngx_resolver_create(ngx_conf_t *cf, ngx_str_t *names, ngx_uint_t n)
{
    ngx_str_t                   s;
    ngx_url_t                   u;
    ngx_uint_t                  i, j;
    ngx_resolver_t             *r;
    ngx_pool_cleanup_t         *cln;
    ngx_resolver_connection_t  *rec;

    r = ngx_pcalloc(cf->pool, sizeof(ngx_resolver_t));
    if (r == NULL) {
        return NULL;
    }

    r->event = ngx_pcalloc(cf->pool, sizeof(ngx_event_t));
    if (r->event == NULL) {
        return NULL;
    }

    cln = ngx_pool_cleanup_add(cf->pool, 0);
    if (cln == NULL) {
        return NULL;
    }

    cln->handler = ngx_resolver_cleanup;
    cln->data = r;

    ngx_rbtree_init(&r->name_rbtree, &r->name_sentinel,
                    ngx_resolver_rbtree_insert_value);

    ngx_rbtree_init(&r->srv_rbtree, &r->srv_sentinel,
                    ngx_resolver_rbtree_insert_value);

    ngx_rbtree_init(&r->addr_rbtree, &r->addr_sentinel,
                    ngx_rbtree_insert_value);

    ngx_queue_init(&r->name_resend_queue);
    ngx_queue_init(&r->srv_resend_queue);
    ngx_queue_init(&r->addr_resend_queue);

    ngx_queue_init(&r->name_expire_queue);
    ngx_queue_init(&r->srv_expire_queue);
    ngx_queue_init(&r->addr_expire_queue);

#if (NGX_HAVE_INET6)
    r->ipv6 = 1;

    ngx_rbtree_init(&r->addr6_rbtree, &r->addr6_sentinel,
                    ngx_resolver_rbtree_insert_addr6_value);

    ngx_queue_init(&r->addr6_resend_queue);

    ngx_queue_init(&r->addr6_expire_queue);
#endif

    r->event->handler = ngx_resolver_resend_handler;
    r->event->data = r;
    r->event->log = &cf->cycle->new_log;
    r->event->cancelable = 1;
    r->ident = -1;

    r->resend_timeout = 5;
    r->tcp_timeout = 5;
    r->expire = 30;
    r->valid = 0;

    r->log = &cf->cycle->new_log;
    r->log_level = NGX_LOG_ERR;

    if (n) {
        if (ngx_array_init(&r->connections, cf->pool, n,
                           sizeof(ngx_resolver_connection_t))
            != NGX_OK)
        {
            return NULL;
        }
    }

    for (i = 0; i < n; i++) {
        if (ngx_strncmp(names[i].data, "valid=", 6) == 0) {
            s.len = names[i].len - 6;
            s.data = names[i].data + 6;

            r->valid = ngx_parse_time(&s, 1);

            if (r->valid == (time_t) NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid parameter: %V", &names[i]);
                return NULL;
            }

            continue;
        }

#if (NGX_HAVE_INET6)
        if (ngx_strncmp(names[i].data, "ipv6=", 5) == 0) {

            if (ngx_strcmp(&names[i].data[5], "on") == 0) {
                r->ipv6 = 1;

            } else if (ngx_strcmp(&names[i].data[5], "off") == 0) {
                r->ipv6 = 0;

            } else {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid parameter: %V", &names[i]);
                return NULL;
            }

            continue;
        }
#endif

        ngx_memzero(&u, sizeof(ngx_url_t));

        u.url = names[i];
        u.default_port = 53;

        if (ngx_parse_url(cf->pool, &u) != NGX_OK) {
            if (u.err) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "%s in resolver \"%V\"",
                                   u.err, &u.url);
            }

            return NULL;
        }

        rec = ngx_array_push_n(&r->connections, u.naddrs);
        if (rec == NULL) {
            return NULL;
        }

        ngx_memzero(rec, u.naddrs * sizeof(ngx_resolver_connection_t));

        for (j = 0; j < u.naddrs; j++) {
            rec[j].sockaddr = u.addrs[j].sockaddr;
            rec[j].socklen = u.addrs[j].socklen;
            rec[j].server = u.addrs[j].name;
            rec[j].resolver = r;
        }
    }

    if (n && r->connections.nelts == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "no name servers defined");
        return NULL;
    }

    return r;
}