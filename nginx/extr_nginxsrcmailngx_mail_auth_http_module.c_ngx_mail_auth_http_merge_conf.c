#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_12__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {TYPE_4__ value; TYPE_3__ key; } ;
typedef  TYPE_5__ ngx_table_elt_t ;
struct TYPE_9__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {TYPE_2__* headers; TYPE_1__ header; int /*<<< orphan*/  pass_client_cert; int /*<<< orphan*/  timeout; int /*<<< orphan*/  line; int /*<<< orphan*/  file; int /*<<< orphan*/ * peer; int /*<<< orphan*/  uri; int /*<<< orphan*/  host_header; } ;
typedef  TYPE_6__ ngx_mail_auth_http_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_7__ ngx_conf_t ;
struct TYPE_10__ {size_t nelts; TYPE_5__* elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  LF ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_cpymem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static char *
ngx_mail_auth_http_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_mail_auth_http_conf_t *prev = parent;
    ngx_mail_auth_http_conf_t *conf = child;

    u_char           *p;
    size_t            len;
    ngx_uint_t        i;
    ngx_table_elt_t  *header;

    if (conf->peer == NULL) {
        conf->peer = prev->peer;
        conf->host_header = prev->host_header;
        conf->uri = prev->uri;

        if (conf->peer == NULL) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "no \"auth_http\" is defined for server in %s:%ui",
                          conf->file, conf->line);

            return NGX_CONF_ERROR;
        }
    }

    ngx_conf_merge_msec_value(conf->timeout, prev->timeout, 60000);

    ngx_conf_merge_value(conf->pass_client_cert, prev->pass_client_cert, 0);

    if (conf->headers == NULL) {
        conf->headers = prev->headers;
        conf->header = prev->header;
    }

    if (conf->headers && conf->header.len == 0) {
        len = 0;
        header = conf->headers->elts;
        for (i = 0; i < conf->headers->nelts; i++) {
            len += header[i].key.len + 2 + header[i].value.len + 2;
        }

        p = ngx_pnalloc(cf->pool, len);
        if (p == NULL) {
            return NGX_CONF_ERROR;
        }

        conf->header.len = len;
        conf->header.data = p;

        for (i = 0; i < conf->headers->nelts; i++) {
            p = ngx_cpymem(p, header[i].key.data, header[i].key.len);
            *p++ = ':'; *p++ = ' ';
            p = ngx_cpymem(p, header[i].value.data, header[i].value.len);
            *p++ = CR; *p++ = LF;
        }
    }

    return NGX_CONF_OK;
}