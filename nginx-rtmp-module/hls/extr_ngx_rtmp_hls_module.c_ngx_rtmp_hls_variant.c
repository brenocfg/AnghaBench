#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  void* ngx_str_t ;
struct TYPE_9__ {int /*<<< orphan*/  args; void* suffix; } ;
typedef  TYPE_2__ ngx_rtmp_hls_variant_t ;
struct TYPE_10__ {int /*<<< orphan*/ * variant; } ;
typedef  TYPE_3__ ngx_rtmp_hls_app_conf_t ;
struct TYPE_11__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_8__ {void** elts; int nelts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* ngx_array_push (int /*<<< orphan*/ *) ; 
 void** ngx_array_push_n (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_2__*,int) ; 

__attribute__((used)) static char *
ngx_rtmp_hls_variant(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_rtmp_hls_app_conf_t  *hacf = conf;

    ngx_str_t                *value, *arg;
    ngx_uint_t                n;
    ngx_rtmp_hls_variant_t   *var;

    value = cf->args->elts;

    if (hacf->variant == NULL) {
        hacf->variant = ngx_array_create(cf->pool, 1,
                                         sizeof(ngx_rtmp_hls_variant_t));
        if (hacf->variant == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    var = ngx_array_push(hacf->variant);
    if (var == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_memzero(var, sizeof(ngx_rtmp_hls_variant_t));

    var->suffix = value[1];

    if (cf->args->nelts == 2) {
        return NGX_CONF_OK;
    }

    if (ngx_array_init(&var->args, cf->pool, cf->args->nelts - 2,
                       sizeof(ngx_str_t))
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    arg = ngx_array_push_n(&var->args, cf->args->nelts - 2);
    if (arg == NULL) {
        return NGX_CONF_ERROR;
    }

    for (n = 2; n < cf->args->nelts; n++) {
        *arg++ = value[n];
    }

    return NGX_CONF_OK;
}