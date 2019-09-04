#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nelts; int /*<<< orphan*/  elts; } ;
struct TYPE_9__ {TYPE_1__ keys; } ;
struct TYPE_10__ {TYPE_2__ commands; int /*<<< orphan*/  hash; } ;
typedef  TYPE_3__ ngx_http_ssi_main_conf_t ;
struct TYPE_11__ {int max_size; char* name; int /*<<< orphan*/ * temp_pool; int /*<<< orphan*/  pool; int /*<<< orphan*/  bucket_size; int /*<<< orphan*/  key; int /*<<< orphan*/ * hash; } ;
typedef  TYPE_4__ ngx_hash_init_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_cacheline_size ; 
 scalar_t__ ngx_hash_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_hash_key ; 

__attribute__((used)) static char *
ngx_http_ssi_init_main_conf(ngx_conf_t *cf, void *conf)
{
    ngx_http_ssi_main_conf_t *smcf = conf;

    ngx_hash_init_t  hash;

    hash.hash = &smcf->hash;
    hash.key = ngx_hash_key;
    hash.max_size = 1024;
    hash.bucket_size = ngx_cacheline_size;
    hash.name = "ssi_command_hash";
    hash.pool = cf->pool;
    hash.temp_pool = NULL;

    if (ngx_hash_init(&hash, smcf->commands.keys.elts,
                      smcf->commands.keys.nelts)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}