#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_11__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_24__ {int /*<<< orphan*/ * buckets; } ;
struct TYPE_22__ {int /*<<< orphan*/ * data; } ;
struct TYPE_29__ {int /*<<< orphan*/ * data; } ;
struct TYPE_25__ {int /*<<< orphan*/  open_file_cache_events; int /*<<< orphan*/  open_file_cache_errors; int /*<<< orphan*/  open_file_cache_min_uses; int /*<<< orphan*/  open_file_cache_valid; int /*<<< orphan*/  open_file_cache; int /*<<< orphan*/  server_tokens; int /*<<< orphan*/  etag; int /*<<< orphan*/  chunked_transfer_encoding; int /*<<< orphan*/  recursive_error_pages; int /*<<< orphan*/  log_subrequest; int /*<<< orphan*/  log_not_found; int /*<<< orphan*/  msie_refresh; int /*<<< orphan*/  msie_padding; int /*<<< orphan*/  port_in_redirect; int /*<<< orphan*/  server_name_in_redirect; int /*<<< orphan*/  absolute_redirect; int /*<<< orphan*/  reset_timedout_connection; int /*<<< orphan*/  client_body_temp_path; int /*<<< orphan*/ * resolver; int /*<<< orphan*/  resolver_timeout; int /*<<< orphan*/  lingering_timeout; int /*<<< orphan*/  lingering_time; int /*<<< orphan*/  lingering_close; int /*<<< orphan*/  keepalive_requests; int /*<<< orphan*/  keepalive_header; int /*<<< orphan*/  keepalive_timeout; int /*<<< orphan*/ * limit_rate_after; int /*<<< orphan*/ * limit_rate; int /*<<< orphan*/  postpone_output; int /*<<< orphan*/  send_lowat; int /*<<< orphan*/  send_timeout; int /*<<< orphan*/  tcp_nodelay; int /*<<< orphan*/  tcp_nopush; int /*<<< orphan*/  directio_alignment; int /*<<< orphan*/  directio; int /*<<< orphan*/  read_ahead; int /*<<< orphan*/  aio_write; int /*<<< orphan*/  aio; int /*<<< orphan*/  subrequest_output_buffer_size; int /*<<< orphan*/  sendfile_max_chunk; int /*<<< orphan*/  sendfile; int /*<<< orphan*/  internal; int /*<<< orphan*/  client_body_in_single_buffer; int /*<<< orphan*/  client_body_in_file_only; int /*<<< orphan*/  max_ranges; int /*<<< orphan*/  if_modified_since; int /*<<< orphan*/  satisfy; int /*<<< orphan*/  keepalive_disable; int /*<<< orphan*/  client_body_timeout; int /*<<< orphan*/  client_body_buffer_size; int /*<<< orphan*/  client_max_body_size; int /*<<< orphan*/  default_type; int /*<<< orphan*/ * error_pages; int /*<<< orphan*/ * error_log; TYPE_17__* types; int /*<<< orphan*/  types_hash_bucket_size; int /*<<< orphan*/  types_hash_max_size; TYPE_3__ types_hash; TYPE_1__ post_action; TYPE_8__ root; int /*<<< orphan*/  root_values; int /*<<< orphan*/  root_lengths; int /*<<< orphan*/  alias; } ;
typedef  TYPE_4__ ngx_http_core_loc_conf_t ;
struct TYPE_23__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_26__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key_hash; TYPE_2__ key; } ;
typedef  TYPE_5__ ngx_hash_key_t ;
struct TYPE_27__ {char* name; int /*<<< orphan*/ * temp_pool; int /*<<< orphan*/  pool; int /*<<< orphan*/  bucket_size; int /*<<< orphan*/  max_size; int /*<<< orphan*/  (* key ) (int /*<<< orphan*/ ,scalar_t__) ;TYPE_3__* hash; } ;
typedef  TYPE_6__ ngx_hash_init_t ;
struct TYPE_28__ {TYPE_14__* cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;
struct TYPE_21__ {int /*<<< orphan*/  nelts; int /*<<< orphan*/  elts; } ;
struct TYPE_20__ {int /*<<< orphan*/  new_log; } ;
struct TYPE_19__ {int /*<<< orphan*/  value; TYPE_2__ key; } ;

/* Variables and functions */
 int NGX_CONF_BITMASK_SET ; 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int NGX_HTTP_AIO_OFF ; 
 int NGX_HTTP_IMS_EXACT ; 
 int NGX_HTTP_KEEPALIVE_DISABLE_MSIE6 ; 
 int NGX_HTTP_LINGERING_ON ; 
 int NGX_HTTP_REQUEST_BODY_FILE_OFF ; 
 int NGX_HTTP_SATISFY_ALL ; 
 int NGX_HTTP_SERVER_TOKENS_ON ; 
 int NGX_MAX_INT32_VALUE ; 
 scalar_t__ NGX_OK ; 
 int NGX_OPEN_FILE_DIRECTIO_OFF ; 
 int /*<<< orphan*/  ngx_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_17__* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__* ngx_array_push (TYPE_17__*) ; 
 int /*<<< orphan*/  ngx_cacheline_size ; 
 scalar_t__ ngx_conf_full_name (TYPE_14__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_merge_bitmask_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_off_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_conf_merge_path_value (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_sec_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_str_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_hash_init (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_hash_key_lc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_client_temp_path ; 
 TYPE_11__* ngx_http_core_default_types ; 
 size_t ngx_pagesize ; 
 int /*<<< orphan*/ * ngx_resolver_create (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_8__*,char*) ; 

__attribute__((used)) static char *
ngx_http_core_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_core_loc_conf_t *prev = parent;
    ngx_http_core_loc_conf_t *conf = child;

    ngx_uint_t        i;
    ngx_hash_key_t   *type;
    ngx_hash_init_t   types_hash;

    if (conf->root.data == NULL) {

        conf->alias = prev->alias;
        conf->root = prev->root;
        conf->root_lengths = prev->root_lengths;
        conf->root_values = prev->root_values;

        if (prev->root.data == NULL) {
            ngx_str_set(&conf->root, "html");

            if (ngx_conf_full_name(cf->cycle, &conf->root, 0) != NGX_OK) {
                return NGX_CONF_ERROR;
            }
        }
    }

    if (conf->post_action.data == NULL) {
        conf->post_action = prev->post_action;
    }

    ngx_conf_merge_uint_value(conf->types_hash_max_size,
                              prev->types_hash_max_size, 1024);

    ngx_conf_merge_uint_value(conf->types_hash_bucket_size,
                              prev->types_hash_bucket_size, 64);

    conf->types_hash_bucket_size = ngx_align(conf->types_hash_bucket_size,
                                             ngx_cacheline_size);

    /*
     * the special handling of the "types" directive in the "http" section
     * to inherit the http's conf->types_hash to all servers
     */

    if (prev->types && prev->types_hash.buckets == NULL) {

        types_hash.hash = &prev->types_hash;
        types_hash.key = ngx_hash_key_lc;
        types_hash.max_size = conf->types_hash_max_size;
        types_hash.bucket_size = conf->types_hash_bucket_size;
        types_hash.name = "types_hash";
        types_hash.pool = cf->pool;
        types_hash.temp_pool = NULL;

        if (ngx_hash_init(&types_hash, prev->types->elts, prev->types->nelts)
            != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }
    }

    if (conf->types == NULL) {
        conf->types = prev->types;
        conf->types_hash = prev->types_hash;
    }

    if (conf->types == NULL) {
        conf->types = ngx_array_create(cf->pool, 3, sizeof(ngx_hash_key_t));
        if (conf->types == NULL) {
            return NGX_CONF_ERROR;
        }

        for (i = 0; ngx_http_core_default_types[i].key.len; i++) {
            type = ngx_array_push(conf->types);
            if (type == NULL) {
                return NGX_CONF_ERROR;
            }

            type->key = ngx_http_core_default_types[i].key;
            type->key_hash =
                       ngx_hash_key_lc(ngx_http_core_default_types[i].key.data,
                                       ngx_http_core_default_types[i].key.len);
            type->value = ngx_http_core_default_types[i].value;
        }
    }

    if (conf->types_hash.buckets == NULL) {

        types_hash.hash = &conf->types_hash;
        types_hash.key = ngx_hash_key_lc;
        types_hash.max_size = conf->types_hash_max_size;
        types_hash.bucket_size = conf->types_hash_bucket_size;
        types_hash.name = "types_hash";
        types_hash.pool = cf->pool;
        types_hash.temp_pool = NULL;

        if (ngx_hash_init(&types_hash, conf->types->elts, conf->types->nelts)
            != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }
    }

    if (conf->error_log == NULL) {
        if (prev->error_log) {
            conf->error_log = prev->error_log;
        } else {
            conf->error_log = &cf->cycle->new_log;
        }
    }

    if (conf->error_pages == NULL && prev->error_pages) {
        conf->error_pages = prev->error_pages;
    }

    ngx_conf_merge_str_value(conf->default_type,
                              prev->default_type, "text/plain");

    ngx_conf_merge_off_value(conf->client_max_body_size,
                              prev->client_max_body_size, 1 * 1024 * 1024);
    ngx_conf_merge_size_value(conf->client_body_buffer_size,
                              prev->client_body_buffer_size,
                              (size_t) 2 * ngx_pagesize);
    ngx_conf_merge_msec_value(conf->client_body_timeout,
                              prev->client_body_timeout, 60000);

    ngx_conf_merge_bitmask_value(conf->keepalive_disable,
                              prev->keepalive_disable,
                              (NGX_CONF_BITMASK_SET
                               |NGX_HTTP_KEEPALIVE_DISABLE_MSIE6));
    ngx_conf_merge_uint_value(conf->satisfy, prev->satisfy,
                              NGX_HTTP_SATISFY_ALL);
    ngx_conf_merge_uint_value(conf->if_modified_since, prev->if_modified_since,
                              NGX_HTTP_IMS_EXACT);
    ngx_conf_merge_uint_value(conf->max_ranges, prev->max_ranges,
                              NGX_MAX_INT32_VALUE);
    ngx_conf_merge_uint_value(conf->client_body_in_file_only,
                              prev->client_body_in_file_only,
                              NGX_HTTP_REQUEST_BODY_FILE_OFF);
    ngx_conf_merge_value(conf->client_body_in_single_buffer,
                              prev->client_body_in_single_buffer, 0);
    ngx_conf_merge_value(conf->internal, prev->internal, 0);
    ngx_conf_merge_value(conf->sendfile, prev->sendfile, 0);
    ngx_conf_merge_size_value(conf->sendfile_max_chunk,
                              prev->sendfile_max_chunk, 0);
    ngx_conf_merge_size_value(conf->subrequest_output_buffer_size,
                              prev->subrequest_output_buffer_size,
                              (size_t) ngx_pagesize);
    ngx_conf_merge_value(conf->aio, prev->aio, NGX_HTTP_AIO_OFF);
    ngx_conf_merge_value(conf->aio_write, prev->aio_write, 0);
#if (NGX_THREADS)
    ngx_conf_merge_ptr_value(conf->thread_pool, prev->thread_pool, NULL);
    ngx_conf_merge_ptr_value(conf->thread_pool_value, prev->thread_pool_value,
                             NULL);
#endif
    ngx_conf_merge_size_value(conf->read_ahead, prev->read_ahead, 0);
    ngx_conf_merge_off_value(conf->directio, prev->directio,
                              NGX_OPEN_FILE_DIRECTIO_OFF);
    ngx_conf_merge_off_value(conf->directio_alignment, prev->directio_alignment,
                              512);
    ngx_conf_merge_value(conf->tcp_nopush, prev->tcp_nopush, 0);
    ngx_conf_merge_value(conf->tcp_nodelay, prev->tcp_nodelay, 1);

    ngx_conf_merge_msec_value(conf->send_timeout, prev->send_timeout, 60000);
    ngx_conf_merge_size_value(conf->send_lowat, prev->send_lowat, 0);
    ngx_conf_merge_size_value(conf->postpone_output, prev->postpone_output,
                              1460);

    if (conf->limit_rate == NULL) {
        conf->limit_rate = prev->limit_rate;
    }

    if (conf->limit_rate_after == NULL) {
        conf->limit_rate_after = prev->limit_rate_after;
    }

    ngx_conf_merge_msec_value(conf->keepalive_timeout,
                              prev->keepalive_timeout, 75000);
    ngx_conf_merge_sec_value(conf->keepalive_header,
                              prev->keepalive_header, 0);
    ngx_conf_merge_uint_value(conf->keepalive_requests,
                              prev->keepalive_requests, 100);
    ngx_conf_merge_uint_value(conf->lingering_close,
                              prev->lingering_close, NGX_HTTP_LINGERING_ON);
    ngx_conf_merge_msec_value(conf->lingering_time,
                              prev->lingering_time, 30000);
    ngx_conf_merge_msec_value(conf->lingering_timeout,
                              prev->lingering_timeout, 5000);
    ngx_conf_merge_msec_value(conf->resolver_timeout,
                              prev->resolver_timeout, 30000);

    if (conf->resolver == NULL) {

        if (prev->resolver == NULL) {

            /*
             * create dummy resolver in http {} context
             * to inherit it in all servers
             */

            prev->resolver = ngx_resolver_create(cf, NULL, 0);
            if (prev->resolver == NULL) {
                return NGX_CONF_ERROR;
            }
        }

        conf->resolver = prev->resolver;
    }

    if (ngx_conf_merge_path_value(cf, &conf->client_body_temp_path,
                              prev->client_body_temp_path,
                              &ngx_http_client_temp_path)
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    ngx_conf_merge_value(conf->reset_timedout_connection,
                              prev->reset_timedout_connection, 0);
    ngx_conf_merge_value(conf->absolute_redirect,
                              prev->absolute_redirect, 1);
    ngx_conf_merge_value(conf->server_name_in_redirect,
                              prev->server_name_in_redirect, 0);
    ngx_conf_merge_value(conf->port_in_redirect, prev->port_in_redirect, 1);
    ngx_conf_merge_value(conf->msie_padding, prev->msie_padding, 1);
    ngx_conf_merge_value(conf->msie_refresh, prev->msie_refresh, 0);
    ngx_conf_merge_value(conf->log_not_found, prev->log_not_found, 1);
    ngx_conf_merge_value(conf->log_subrequest, prev->log_subrequest, 0);
    ngx_conf_merge_value(conf->recursive_error_pages,
                              prev->recursive_error_pages, 0);
    ngx_conf_merge_value(conf->chunked_transfer_encoding,
                              prev->chunked_transfer_encoding, 1);
    ngx_conf_merge_value(conf->etag, prev->etag, 1);

    ngx_conf_merge_uint_value(conf->server_tokens, prev->server_tokens,
                              NGX_HTTP_SERVER_TOKENS_ON);

    ngx_conf_merge_ptr_value(conf->open_file_cache,
                              prev->open_file_cache, NULL);

    ngx_conf_merge_sec_value(conf->open_file_cache_valid,
                              prev->open_file_cache_valid, 60);

    ngx_conf_merge_uint_value(conf->open_file_cache_min_uses,
                              prev->open_file_cache_min_uses, 1);

    ngx_conf_merge_sec_value(conf->open_file_cache_errors,
                              prev->open_file_cache_errors, 0);

    ngx_conf_merge_sec_value(conf->open_file_cache_events,
                              prev->open_file_cache_events, 0);
#if (NGX_HTTP_GZIP)

    ngx_conf_merge_value(conf->gzip_vary, prev->gzip_vary, 0);
    ngx_conf_merge_uint_value(conf->gzip_http_version, prev->gzip_http_version,
                              NGX_HTTP_VERSION_11);
    ngx_conf_merge_bitmask_value(conf->gzip_proxied, prev->gzip_proxied,
                              (NGX_CONF_BITMASK_SET|NGX_HTTP_GZIP_PROXIED_OFF));

#if (NGX_PCRE)
    ngx_conf_merge_ptr_value(conf->gzip_disable, prev->gzip_disable, NULL);
#endif

    if (conf->gzip_disable_msie6 == 3) {
        conf->gzip_disable_msie6 =
            (prev->gzip_disable_msie6 == 3) ? 0 : prev->gzip_disable_msie6;
    }

#if (NGX_HTTP_DEGRADATION)

    if (conf->gzip_disable_degradation == 3) {
        conf->gzip_disable_degradation =
            (prev->gzip_disable_degradation == 3) ?
                 0 : prev->gzip_disable_degradation;
    }

#endif
#endif

#if (NGX_HAVE_OPENAT)
    ngx_conf_merge_uint_value(conf->disable_symlinks, prev->disable_symlinks,
                              NGX_DISABLE_SYMLINKS_OFF);
    ngx_conf_merge_ptr_value(conf->disable_symlinks_from,
                             prev->disable_symlinks_from, NULL);
#endif

    return NGX_CONF_OK;
}