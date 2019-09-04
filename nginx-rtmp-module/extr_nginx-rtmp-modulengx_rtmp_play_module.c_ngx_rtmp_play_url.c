#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_15__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_18__ {int default_port; int uri_part; TYPE_11__ url; scalar_t__ err; } ;
typedef  TYPE_2__ ngx_url_t ;
struct TYPE_19__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_20__ {TYPE_2__* url; TYPE_3__* root; } ;
typedef  TYPE_4__ ngx_rtmp_play_entry_t ;
struct TYPE_16__ {scalar_t__ nalloc; } ;
struct TYPE_21__ {TYPE_13__ entries; } ;
typedef  TYPE_5__ ngx_rtmp_play_app_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_17__ {size_t nelts; TYPE_3__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_13__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_4__** ngx_array_push (TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,scalar_t__,TYPE_11__*) ; 
 TYPE_3__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
ngx_rtmp_play_url(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_rtmp_play_app_conf_t       *pacf = conf;

    ngx_rtmp_play_entry_t          *pe, **ppe;
    ngx_str_t                       url;
    ngx_url_t                      *u;
    size_t                          add, n;
    ngx_str_t                      *value;

    if (pacf->entries.nalloc == 0 &&
        ngx_array_init(&pacf->entries, cf->pool, 1, sizeof(void *)) != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;

    for (n = 1; n < cf->args->nelts; ++n) {

        ppe = ngx_array_push(&pacf->entries);
        if (ppe == NULL) {
            return NGX_CONF_ERROR;
        }

        pe = ngx_pcalloc(cf->pool, sizeof(ngx_rtmp_play_entry_t));
        if (pe == NULL) {
            return NGX_CONF_ERROR;
        }

        *ppe = pe;

        if (ngx_strncasecmp(value[n].data, (u_char *) "http://", 7)) {

            /* local file */

            pe->root = ngx_palloc(cf->pool, sizeof(ngx_str_t));
            if (pe->root == NULL) {
                return NGX_CONF_ERROR;
            }

            *pe->root = value[n];

            continue;
        }

        /* http case */

        url = value[n];

        add = sizeof("http://") - 1;

        url.data += add;
        url.len  -= add;

        u = ngx_pcalloc(cf->pool, sizeof(ngx_url_t));
        if (u == NULL) {
            return NGX_CONF_ERROR;
        }

        u->url.len = url.len;
        u->url.data = url.data;
        u->default_port = 80;
        u->uri_part = 1;

        if (ngx_parse_url(cf->pool, u) != NGX_OK) {
            if (u->err) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                        "%s in url \"%V\"", u->err, &u->url);
            }
            return NGX_CONF_ERROR;
        }

        pe->url = u;
    }

    return NGX_CONF_OK;
}