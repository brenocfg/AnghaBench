#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_20__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
struct TYPE_24__ {scalar_t__ len; } ;
struct TYPE_22__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_26__ {int no_resolve; scalar_t__ family; TYPE_11__ host; TYPE_4__ port_text; scalar_t__ no_port; TYPE_2__ url; } ;
typedef  TYPE_6__ ngx_url_t ;
struct TYPE_27__ {scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_7__ ngx_str_t ;
struct TYPE_23__ {int /*<<< orphan*/ * upstream; } ;
struct TYPE_28__ {int ssl; TYPE_11__ host; TYPE_3__ upstream; } ;
typedef  TYPE_8__ ngx_http_grpc_loc_conf_t ;
struct TYPE_25__ {int len; char* data; } ;
struct TYPE_29__ {int auto_redirect; TYPE_5__ name; int /*<<< orphan*/  handler; } ;
typedef  TYPE_9__ ngx_http_core_loc_conf_t ;
struct TYPE_19__ {TYPE_1__* args; } ;
typedef  TYPE_10__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_21__ {TYPE_7__* elts; } ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_9__* ngx_http_conf_get_module_loc_conf (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_grpc_handler ; 
 int /*<<< orphan*/ * ngx_http_upstream_add (TYPE_10__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_11__*,char*) ; 
 scalar_t__ ngx_strncasecmp (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
ngx_http_grpc_pass(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_grpc_loc_conf_t *glcf = conf;

    size_t                     add;
    ngx_str_t                 *value, *url;
    ngx_url_t                  u;
    ngx_http_core_loc_conf_t  *clcf;

    if (glcf->upstream.upstream) {
        return "is duplicate";
    }

    value = cf->args->elts;
    url = &value[1];

    if (ngx_strncasecmp(url->data, (u_char *) "grpc://", 7) == 0) {
        add = 7;

    } else if (ngx_strncasecmp(url->data, (u_char *) "grpcs://", 8) == 0) {

#if (NGX_HTTP_SSL)
        glcf->ssl = 1;

        add = 8;
#else
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "grpcs protocol requires SSL support");
        return NGX_CONF_ERROR;
#endif

    } else {
        add = 0;
    }

    ngx_memzero(&u, sizeof(ngx_url_t));

    u.url.len = url->len - add;
    u.url.data = url->data + add;
    u.no_resolve = 1;

    glcf->upstream.upstream = ngx_http_upstream_add(cf, &u, 0);
    if (glcf->upstream.upstream == NULL) {
        return NGX_CONF_ERROR;
    }

    if (u.family != AF_UNIX) {

        if (u.no_port) {
            glcf->host = u.host;

        } else {
            glcf->host.len = u.host.len + 1 + u.port_text.len;
            glcf->host.data = u.host.data;
        }

    } else {
        ngx_str_set(&glcf->host, "localhost");
    }

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);

    clcf->handler = ngx_http_grpc_handler;

    if (clcf->name.len && clcf->name.data[clcf->name.len - 1] == '/') {
        clcf->auto_redirect = 1;
    }

    return NGX_CONF_OK;
}