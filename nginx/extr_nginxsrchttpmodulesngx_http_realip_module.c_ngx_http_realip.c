#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ header; int /*<<< orphan*/  hash; } ;
typedef  TYPE_3__ ngx_http_realip_loc_conf_t ;
struct TYPE_9__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_6__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET_UINT ; 
 scalar_t__ NGX_HTTP_REALIP_HEADER ; 
 scalar_t__ NGX_HTTP_REALIP_PROXY ; 
 scalar_t__ NGX_HTTP_REALIP_XFWD ; 
 scalar_t__ NGX_HTTP_REALIP_XREALIP ; 
 int /*<<< orphan*/  ngx_hash_strlow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
ngx_http_realip(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_realip_loc_conf_t *rlcf = conf;

    ngx_str_t  *value;

    if (rlcf->type != NGX_CONF_UNSET_UINT) {
        return "is duplicate";
    }

    value = cf->args->elts;

    if (ngx_strcmp(value[1].data, "X-Real-IP") == 0) {
        rlcf->type = NGX_HTTP_REALIP_XREALIP;
        return NGX_CONF_OK;
    }

    if (ngx_strcmp(value[1].data, "X-Forwarded-For") == 0) {
        rlcf->type = NGX_HTTP_REALIP_XFWD;
        return NGX_CONF_OK;
    }

    if (ngx_strcmp(value[1].data, "proxy_protocol") == 0) {
        rlcf->type = NGX_HTTP_REALIP_PROXY;
        return NGX_CONF_OK;
    }

    rlcf->type = NGX_HTTP_REALIP_HEADER;
    rlcf->hash = ngx_hash_strlow(value[1].data, value[1].data, value[1].len);
    rlcf->header = value[1];

    return NGX_CONF_OK;
}