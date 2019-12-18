#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_24__ {scalar_t__ (* init_upstream ) (TYPE_6__*,TYPE_4__*) ;} ;
struct TYPE_26__ {TYPE_2__ peer; } ;
typedef  TYPE_4__ ngx_http_upstream_srv_conf_t ;
struct TYPE_23__ {size_t nelts; TYPE_4__** elts; } ;
struct TYPE_27__ {int /*<<< orphan*/  headers_in_hash; TYPE_1__ upstreams; } ;
typedef  TYPE_5__ ngx_http_upstream_main_conf_t ;
typedef  scalar_t__ (* ngx_http_upstream_init_pt ) (TYPE_6__*,TYPE_4__*) ;
struct TYPE_25__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_29__ {TYPE_3__ name; } ;
typedef  TYPE_8__ ngx_http_upstream_header_t ;
struct TYPE_30__ {TYPE_8__* value; int /*<<< orphan*/  key_hash; TYPE_3__ key; } ;
typedef  TYPE_9__ ngx_hash_key_t ;
struct TYPE_21__ {int max_size; char* name; int /*<<< orphan*/ * temp_pool; int /*<<< orphan*/  pool; int /*<<< orphan*/  bucket_size; int /*<<< orphan*/  (* key ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/ * hash; } ;
typedef  TYPE_10__ ngx_hash_init_t ;
struct TYPE_28__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  nelts; int /*<<< orphan*/  elts; } ;
typedef  TYPE_12__ ngx_array_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_align (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_array_init (TYPE_12__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_9__* ngx_array_push (TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_cacheline_size ; 
 scalar_t__ ngx_hash_init (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_hash_key_lc (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_8__* ngx_http_upstream_headers_in ; 
 scalar_t__ ngx_http_upstream_init_round_robin (TYPE_6__*,TYPE_4__*) ; 

__attribute__((used)) static char *
ngx_http_upstream_init_main_conf(ngx_conf_t *cf, void *conf)
{
    ngx_http_upstream_main_conf_t  *umcf = conf;

    ngx_uint_t                      i;
    ngx_array_t                     headers_in;
    ngx_hash_key_t                 *hk;
    ngx_hash_init_t                 hash;
    ngx_http_upstream_init_pt       init;
    ngx_http_upstream_header_t     *header;
    ngx_http_upstream_srv_conf_t  **uscfp;

    uscfp = umcf->upstreams.elts;

    for (i = 0; i < umcf->upstreams.nelts; i++) {

        init = uscfp[i]->peer.init_upstream ? uscfp[i]->peer.init_upstream:
                                            ngx_http_upstream_init_round_robin;

        if (init(cf, uscfp[i]) != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }


    /* upstream_headers_in_hash */

    if (ngx_array_init(&headers_in, cf->temp_pool, 32, sizeof(ngx_hash_key_t))
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    for (header = ngx_http_upstream_headers_in; header->name.len; header++) {
        hk = ngx_array_push(&headers_in);
        if (hk == NULL) {
            return NGX_CONF_ERROR;
        }

        hk->key = header->name;
        hk->key_hash = ngx_hash_key_lc(header->name.data, header->name.len);
        hk->value = header;
    }

    hash.hash = &umcf->headers_in_hash;
    hash.key = ngx_hash_key_lc;
    hash.max_size = 512;
    hash.bucket_size = ngx_align(64, ngx_cacheline_size);
    hash.name = "upstream_headers_in_hash";
    hash.pool = cf->pool;
    hash.temp_pool = NULL;

    if (ngx_hash_init(&hash, headers_in.elts, headers_in.nelts) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}