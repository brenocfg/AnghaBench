#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_9__ {int /*<<< orphan*/ * args; int /*<<< orphan*/ * type; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ ngx_rtmp_publish_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/ * next; TYPE_3__* buf; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_11__ {int /*<<< orphan*/ * last; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ESCAPE_ARGS ; 
 int /*<<< orphan*/  NGX_RTMP_NOTIFY_PUBLISH ; 
 TYPE_2__* ngx_alloc_chain_link (int /*<<< orphan*/ *) ; 
 void* ngx_cpymem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 TYPE_3__* ngx_create_temp_buf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ngx_escape_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_rtmp_notify_create_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 size_t ngx_strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_chain_t *
ngx_rtmp_notify_publish_create(ngx_rtmp_session_t *s, void *arg,
        ngx_pool_t *pool)
{
    ngx_rtmp_publish_t             *v = arg;

    ngx_chain_t                    *pl;
    ngx_buf_t                      *b;
    size_t                          name_len, type_len, args_len;

    pl = ngx_alloc_chain_link(pool);
    if (pl == NULL) {
        return NULL;
    }

    name_len = ngx_strlen(v->name);
    type_len = ngx_strlen(v->type);
    args_len = ngx_strlen(v->args);

    b = ngx_create_temp_buf(pool,
                            sizeof("&call=publish") +
                            sizeof("&name=") + name_len * 3 +
                            sizeof("&type=") + type_len * 3 +
                            1 + args_len);
    if (b == NULL) {
        return NULL;
    }

    pl->buf = b;
    pl->next = NULL;

    b->last = ngx_cpymem(b->last, (u_char*) "&call=publish",
                         sizeof("&call=publish") - 1);

    b->last = ngx_cpymem(b->last, (u_char*) "&name=", sizeof("&name=") - 1);
    b->last = (u_char*) ngx_escape_uri(b->last, v->name, name_len,
                                       NGX_ESCAPE_ARGS);

    b->last = ngx_cpymem(b->last, (u_char*) "&type=", sizeof("&type=") - 1);
    b->last = (u_char*) ngx_escape_uri(b->last, v->type, type_len,
                                       NGX_ESCAPE_ARGS);

    if (args_len) {
        *b->last++ = '&';
        b->last = (u_char *) ngx_cpymem(b->last, v->args, args_len);
    }

    return ngx_rtmp_notify_create_request(s, pool, NGX_RTMP_NOTIFY_PUBLISH, pl);
}