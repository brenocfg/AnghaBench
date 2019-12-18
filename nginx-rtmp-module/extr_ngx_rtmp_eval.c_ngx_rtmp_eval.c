#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_8__ {char* data; size_t len; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_eval_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {char* pos; char* last; char* start; char* end; } ;
typedef  TYPE_2__ ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_RTMP_EVAL_BUFLEN ; 
 char* ngx_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_eval_append (TYPE_2__*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_eval_append_var (void*,TYPE_2__*,int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_rtmp_eval(void *ctx, ngx_str_t *in, ngx_rtmp_eval_t **e, ngx_str_t *out,
    ngx_log_t *log)
{
    u_char      c, *p;
    ngx_str_t   name;
    ngx_buf_t   b;
    ngx_uint_t  n;

    enum {
        NORMAL,
        ESCAPE,
        NAME,
        SNAME
    } state = NORMAL;

    b.pos = b.last = b.start = ngx_alloc(NGX_RTMP_EVAL_BUFLEN, log);
    if (b.pos == NULL) {
        return NGX_ERROR;
    }

    b.end = b.pos + NGX_RTMP_EVAL_BUFLEN;
    name.data = NULL;

    for (n = 0; n < in->len; ++n) {
        p = &in->data[n];
        c = *p;

        switch (state) {
            case SNAME:
                if (c != '}') {
                    continue;
                }

                name.len = p - name.data;
                ngx_rtmp_eval_append_var(ctx, &b, e, &name, log);

                state = NORMAL;

                continue;

            case NAME:
                if (c == '{' && name.data == p) {
                    ++name.data;
                    state = SNAME;
                    continue;
                }
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    continue;
                }

                name.len = p - name.data;
                ngx_rtmp_eval_append_var(ctx, &b, e, &name, log);
                /* fall through */

            case NORMAL:
                switch (c) {
                    case '$':
                        name.data = p + 1;
                        state = NAME;
                        continue;
                    case '\\':
                        state = ESCAPE;
                        continue;
                }

            case ESCAPE:
                ngx_rtmp_eval_append(&b, &c, 1, log);
                state = NORMAL;
                break;

        }
    }

    if (state == NAME) {
        p = &in->data[n];
        name.len = p - name.data;
        ngx_rtmp_eval_append_var(ctx, &b, e, &name, log);
    }

    c = 0;
    ngx_rtmp_eval_append(&b, &c, 1, log);

    out->data = b.pos;
    out->len  = b.last - b.pos - 1;

    return NGX_OK;
}