#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_9__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct TYPE_13__ {int len; } ;
struct TYPE_11__ {TYPE_1__ out; TYPE_8__ salt; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  LF ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_base64_encoded_length (int) ; 
 int /*<<< orphan*/  ngx_cpymem (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  ngx_encode_base64 (TYPE_2__*,TYPE_8__*) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,scalar_t__) ; 

ngx_int_t
ngx_mail_auth_cram_md5_salt(ngx_mail_session_t *s, ngx_connection_t *c,
    char *prefix, size_t len)
{
    u_char      *p;
    ngx_str_t    salt;
    ngx_uint_t   n;

    p = ngx_pnalloc(c->pool, len + ngx_base64_encoded_length(s->salt.len) + 2);
    if (p == NULL) {
        return NGX_ERROR;
    }

    salt.data = ngx_cpymem(p, prefix, len);
    s->salt.len -= 2;

    ngx_encode_base64(&salt, &s->salt);

    s->salt.len += 2;
    n = len + salt.len;
    p[n++] = CR; p[n++] = LF;

    s->out.len = n;
    s->out.data = p;

    return NGX_OK;
}