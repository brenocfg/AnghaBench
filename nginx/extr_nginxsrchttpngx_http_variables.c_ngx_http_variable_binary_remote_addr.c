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
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int len; int valid; int /*<<< orphan*/ * data; int /*<<< orphan*/  not_found; int /*<<< orphan*/  no_cacheable; } ;
typedef  TYPE_3__ ngx_http_variable_value_t ;
struct TYPE_10__ {TYPE_2__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  in_addr_t ;
struct TYPE_8__ {TYPE_1__* sockaddr; } ;
struct TYPE_7__ {int sa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_variable_binary_remote_addr(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    struct sockaddr_in   *sin;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6  *sin6;
#endif

    switch (r->connection->sockaddr->sa_family) {

#if (NGX_HAVE_INET6)
    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) r->connection->sockaddr;

        v->len = sizeof(struct in6_addr);
        v->valid = 1;
        v->no_cacheable = 0;
        v->not_found = 0;
        v->data = sin6->sin6_addr.s6_addr;

        break;
#endif

#if (NGX_HAVE_UNIX_DOMAIN)
    case AF_UNIX:

        v->len = r->connection->addr_text.len;
        v->valid = 1;
        v->no_cacheable = 0;
        v->not_found = 0;
        v->data = r->connection->addr_text.data;

        break;
#endif

    default: /* AF_INET */
        sin = (struct sockaddr_in *) r->connection->sockaddr;

        v->len = sizeof(in_addr_t);
        v->valid = 1;
        v->no_cacheable = 0;
        v->not_found = 0;
        v->data = (u_char *) &sin->sin_addr;

        break;
    }

    return NGX_OK;
}