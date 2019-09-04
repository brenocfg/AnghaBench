#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ expires; int /*<<< orphan*/ * trailers; int /*<<< orphan*/ * headers; int /*<<< orphan*/  expires_value; int /*<<< orphan*/  expires_time; } ;
typedef  TYPE_1__ ngx_http_headers_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_HTTP_EXPIRES_OFF ; 
 scalar_t__ NGX_HTTP_EXPIRES_UNSET ; 

__attribute__((used)) static char *
ngx_http_headers_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_headers_conf_t *prev = parent;
    ngx_http_headers_conf_t *conf = child;

    if (conf->expires == NGX_HTTP_EXPIRES_UNSET) {
        conf->expires = prev->expires;
        conf->expires_time = prev->expires_time;
        conf->expires_value = prev->expires_value;

        if (conf->expires == NGX_HTTP_EXPIRES_UNSET) {
            conf->expires = NGX_HTTP_EXPIRES_OFF;
        }
    }

    if (conf->headers == NULL) {
        conf->headers = prev->headers;
    }

    if (conf->trailers == NULL) {
        conf->trailers = prev->trailers;
    }

    return NGX_CONF_OK;
}