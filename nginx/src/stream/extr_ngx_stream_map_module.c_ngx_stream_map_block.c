#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_9__ ;
typedef  struct TYPE_42__   TYPE_8__ ;
typedef  struct TYPE_41__   TYPE_7__ ;
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_27__ ;
typedef  struct TYPE_34__   TYPE_22__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_14__ ;
typedef  struct TYPE_31__   TYPE_13__ ;
typedef  struct TYPE_30__   TYPE_12__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
struct TYPE_41__ {uintptr_t data; int /*<<< orphan*/  flags; int /*<<< orphan*/  get_handler; } ;
typedef  TYPE_7__ ngx_stream_variable_t ;
typedef  int /*<<< orphan*/  ngx_stream_map_regex_t ;
struct TYPE_38__ {int /*<<< orphan*/ * wc_tail; int /*<<< orphan*/ * wc_head; int /*<<< orphan*/  hash; } ;
struct TYPE_39__ {scalar_t__ nregex; int /*<<< orphan*/  regex; TYPE_4__ hash; } ;
struct TYPE_42__ {TYPE_5__ map; scalar_t__ hostnames; int /*<<< orphan*/ * default_value; int /*<<< orphan*/  value; } ;
typedef  TYPE_8__ ngx_stream_map_ctx_t ;
struct TYPE_43__ {scalar_t__ hash_max_size; scalar_t__ hash_bucket_size; } ;
typedef  TYPE_9__ ngx_stream_map_conf_t ;
struct TYPE_35__ {scalar_t__ nelts; int /*<<< orphan*/  elts; } ;
struct TYPE_36__ {scalar_t__ nelts; int /*<<< orphan*/  elts; } ;
struct TYPE_33__ {scalar_t__ nelts; int /*<<< orphan*/  elts; } ;
struct TYPE_40__ {scalar_t__ nelts; int /*<<< orphan*/  elts; } ;
struct TYPE_34__ {int hsize; TYPE_2__ dns_wc_tail; TYPE_1__ dns_wc_head; TYPE_6__ keys; int /*<<< orphan*/ * temp_pool; int /*<<< orphan*/ * pool; } ;
struct TYPE_28__ {TYPE_27__ regexes; TYPE_22__ keys; scalar_t__ hostnames; int /*<<< orphan*/ * default_value; scalar_t__ no_cacheable; TYPE_14__* cf; int /*<<< orphan*/ * values_hash; } ;
typedef  TYPE_10__ ngx_stream_map_conf_ctx_t ;
struct TYPE_29__ {int /*<<< orphan*/ * complex_value; TYPE_12__* value; TYPE_14__* cf; } ;
typedef  TYPE_11__ ngx_stream_compile_complex_value_t ;
struct TYPE_30__ {char* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_12__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_hash_wildcard_t ;
typedef  int /*<<< orphan*/  ngx_hash_key_t ;
struct TYPE_31__ {int max_size; scalar_t__ bucket_size; char* name; int /*<<< orphan*/ * hash; int /*<<< orphan*/ * temp_pool; int /*<<< orphan*/ * pool; int /*<<< orphan*/  key; } ;
typedef  TYPE_13__ ngx_hash_init_t ;
struct TYPE_32__ {int /*<<< orphan*/ * pool; void* handler_conf; int /*<<< orphan*/  handler; TYPE_10__* ctx; int /*<<< orphan*/  log; TYPE_3__* args; } ;
typedef  TYPE_14__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_37__ {TYPE_12__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET_UINT ; 
 int /*<<< orphan*/  NGX_DEFAULT_POOL_SIZE ; 
 int /*<<< orphan*/  NGX_HASH_LARGE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_STREAM_VAR_CHANGEABLE ; 
 int /*<<< orphan*/  NGX_STREAM_VAR_NOCACHEABLE ; 
 scalar_t__ ngx_align (scalar_t__,scalar_t__) ; 
 scalar_t__ ngx_array_init (TYPE_27__*,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ngx_cacheline_size ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_14__*,int /*<<< orphan*/ ,char*,TYPE_12__*) ; 
 char* ngx_conf_parse (TYPE_14__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_create_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_hash_init (TYPE_13__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_hash_key_lc ; 
 scalar_t__ ngx_hash_keys_array_init (TYPE_22__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_hash_wildcard_init (TYPE_13__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_11__*,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_qsort (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_stream_add_variable (TYPE_14__*,TYPE_12__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_stream_compile_complex_value (TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_stream_map ; 
 int /*<<< orphan*/  ngx_stream_map_cmp_dns_wildcards ; 
 int /*<<< orphan*/  ngx_stream_map_variable ; 
 int /*<<< orphan*/  ngx_stream_variable_null_value ; 

__attribute__((used)) static char *
ngx_stream_map_block(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_stream_map_conf_t  *mcf = conf;

    char                                *rv;
    ngx_str_t                           *value, name;
    ngx_conf_t                           save;
    ngx_pool_t                          *pool;
    ngx_hash_init_t                      hash;
    ngx_stream_map_ctx_t                *map;
    ngx_stream_variable_t               *var;
    ngx_stream_map_conf_ctx_t            ctx;
    ngx_stream_compile_complex_value_t   ccv;

    if (mcf->hash_max_size == NGX_CONF_UNSET_UINT) {
        mcf->hash_max_size = 2048;
    }

    if (mcf->hash_bucket_size == NGX_CONF_UNSET_UINT) {
        mcf->hash_bucket_size = ngx_cacheline_size;

    } else {
        mcf->hash_bucket_size = ngx_align(mcf->hash_bucket_size,
                                          ngx_cacheline_size);
    }

    map = ngx_pcalloc(cf->pool, sizeof(ngx_stream_map_ctx_t));
    if (map == NULL) {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;

    ngx_memzero(&ccv, sizeof(ngx_stream_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = &value[1];
    ccv.complex_value = &map->value;

    if (ngx_stream_compile_complex_value(&ccv) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    name = value[2];

    if (name.data[0] != '$') {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid variable name \"%V\"", &name);
        return NGX_CONF_ERROR;
    }

    name.len--;
    name.data++;

    var = ngx_stream_add_variable(cf, &name, NGX_STREAM_VAR_CHANGEABLE);
    if (var == NULL) {
        return NGX_CONF_ERROR;
    }

    var->get_handler = ngx_stream_map_variable;
    var->data = (uintptr_t) map;

    pool = ngx_create_pool(NGX_DEFAULT_POOL_SIZE, cf->log);
    if (pool == NULL) {
        return NGX_CONF_ERROR;
    }

    ctx.keys.pool = cf->pool;
    ctx.keys.temp_pool = pool;

    if (ngx_hash_keys_array_init(&ctx.keys, NGX_HASH_LARGE) != NGX_OK) {
        ngx_destroy_pool(pool);
        return NGX_CONF_ERROR;
    }

    ctx.values_hash = ngx_pcalloc(pool, sizeof(ngx_array_t) * ctx.keys.hsize);
    if (ctx.values_hash == NULL) {
        ngx_destroy_pool(pool);
        return NGX_CONF_ERROR;
    }

#if (NGX_PCRE)
    if (ngx_array_init(&ctx.regexes, cf->pool, 2,
                       sizeof(ngx_stream_map_regex_t))
        != NGX_OK)
    {
        ngx_destroy_pool(pool);
        return NGX_CONF_ERROR;
    }
#endif

    ctx.default_value = NULL;
    ctx.cf = &save;
    ctx.hostnames = 0;
    ctx.no_cacheable = 0;

    save = *cf;
    cf->pool = pool;
    cf->ctx = &ctx;
    cf->handler = ngx_stream_map;
    cf->handler_conf = conf;

    rv = ngx_conf_parse(cf, NULL);

    *cf = save;

    if (rv != NGX_CONF_OK) {
        ngx_destroy_pool(pool);
        return rv;
    }

    if (ctx.no_cacheable) {
        var->flags |= NGX_STREAM_VAR_NOCACHEABLE;
    }

    map->default_value = ctx.default_value ? ctx.default_value:
                                             &ngx_stream_variable_null_value;

    map->hostnames = ctx.hostnames;

    hash.key = ngx_hash_key_lc;
    hash.max_size = mcf->hash_max_size;
    hash.bucket_size = mcf->hash_bucket_size;
    hash.name = "map_hash";
    hash.pool = cf->pool;

    if (ctx.keys.keys.nelts) {
        hash.hash = &map->map.hash.hash;
        hash.temp_pool = NULL;

        if (ngx_hash_init(&hash, ctx.keys.keys.elts, ctx.keys.keys.nelts)
            != NGX_OK)
        {
            ngx_destroy_pool(pool);
            return NGX_CONF_ERROR;
        }
    }

    if (ctx.keys.dns_wc_head.nelts) {

        ngx_qsort(ctx.keys.dns_wc_head.elts,
                  (size_t) ctx.keys.dns_wc_head.nelts,
                  sizeof(ngx_hash_key_t), ngx_stream_map_cmp_dns_wildcards);

        hash.hash = NULL;
        hash.temp_pool = pool;

        if (ngx_hash_wildcard_init(&hash, ctx.keys.dns_wc_head.elts,
                                   ctx.keys.dns_wc_head.nelts)
            != NGX_OK)
        {
            ngx_destroy_pool(pool);
            return NGX_CONF_ERROR;
        }

        map->map.hash.wc_head = (ngx_hash_wildcard_t *) hash.hash;
    }

    if (ctx.keys.dns_wc_tail.nelts) {

        ngx_qsort(ctx.keys.dns_wc_tail.elts,
                  (size_t) ctx.keys.dns_wc_tail.nelts,
                  sizeof(ngx_hash_key_t), ngx_stream_map_cmp_dns_wildcards);

        hash.hash = NULL;
        hash.temp_pool = pool;

        if (ngx_hash_wildcard_init(&hash, ctx.keys.dns_wc_tail.elts,
                                   ctx.keys.dns_wc_tail.nelts)
            != NGX_OK)
        {
            ngx_destroy_pool(pool);
            return NGX_CONF_ERROR;
        }

        map->map.hash.wc_tail = (ngx_hash_wildcard_t *) hash.hash;
    }

#if (NGX_PCRE)

    if (ctx.regexes.nelts) {
        map->map.regex = ctx.regexes.elts;
        map->map.nregex = ctx.regexes.nelts;
    }

#endif

    ngx_destroy_pool(pool);

    return rv;
}