#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_7__ {char* data; int len; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {scalar_t__ len; char* data; } ;
struct TYPE_8__ {TYPE_1__ args; } ;
typedef  TYPE_3__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_OK ; 
 char* ngx_strlcasestrn (char*,char*,char*,size_t) ; 
 char* ngx_strlchr (char*,char*,char) ; 

ngx_int_t
ngx_http_arg(ngx_http_request_t *r, u_char *name, size_t len, ngx_str_t *value)
{
    u_char  *p, *last;

    if (r->args.len == 0) {
        return NGX_DECLINED;
    }

    p = r->args.data;
    last = p + r->args.len;

    for ( /* void */ ; p < last; p++) {

        /* we need '=' after name, so drop one char from last */

        p = ngx_strlcasestrn(p, last - 1, name, len - 1);

        if (p == NULL) {
            return NGX_DECLINED;
        }

        if ((p == r->args.data || *(p - 1) == '&') && *(p + len) == '=') {

            value->data = p + len + 1;

            p = ngx_strlchr(p, last, '&');

            if (p == NULL) {
                p = r->args.data + r->args.len;
            }

            value->len = p - value->data;

            return NGX_OK;
        }
    }

    return NGX_DECLINED;
}