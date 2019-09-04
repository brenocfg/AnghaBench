#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_10__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_11__ {TYPE_1__* connection; scalar_t__ hs_digest; TYPE_4__* hs_buf; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_12__ {scalar_t__ last; scalar_t__ start; scalar_t__ pos; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_RTMP_HANDSHAKE_KEYLEN ; 
 int /*<<< orphan*/  ngx_rtmp_fill_random_buffer (TYPE_4__*) ; 
 scalar_t__ ngx_rtmp_make_digest (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_handshake_create_response(ngx_rtmp_session_t *s)
{
    ngx_buf_t          *b;
    u_char             *p;
    ngx_str_t           key;

    b = s->hs_buf;
    b->pos = b->last = b->start + 1;
    ngx_rtmp_fill_random_buffer(b);
    if (s->hs_digest) {
        p = b->last - NGX_RTMP_HANDSHAKE_KEYLEN;
        key.data = s->hs_digest;
        key.len = NGX_RTMP_HANDSHAKE_KEYLEN;
        if (ngx_rtmp_make_digest(&key, b, p, p, s->connection->log) != NGX_OK) {
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}