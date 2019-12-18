#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_11__ {scalar_t__ len; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_12__ {TYPE_3__* buf; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_13__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  last; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 int NGX_INT_T_LEN ; 
 TYPE_2__* ngx_alloc_chain_link (int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_create_temp_buf (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

ngx_chain_t *
ngx_rtmp_netcall_memcache_set(ngx_rtmp_session_t *s, ngx_pool_t *pool,
        ngx_str_t *key, ngx_str_t *value, ngx_uint_t flags, ngx_uint_t sec)
{
    ngx_chain_t                    *cl;
    ngx_buf_t                      *b;

    cl = ngx_alloc_chain_link(pool);
    if (cl == NULL) {
        return NULL;
    }

    b = ngx_create_temp_buf(pool, sizeof("set ") - 1 + key->len +
                            (1 + NGX_INT_T_LEN) * 3 +
                            (sizeof("\r\n") - 1) * 2 + value->len);

    if (b == NULL) {
        return NULL;
    }

    cl->next = NULL;
    cl->buf = b;

    b->last = ngx_sprintf(b->pos, "set %V %ui %ui %ui\r\n%V\r\n",
                          key, flags, sec, (ngx_uint_t) value->len, value);

    return cl;
}