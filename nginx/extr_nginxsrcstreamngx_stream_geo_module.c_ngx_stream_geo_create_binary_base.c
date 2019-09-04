#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_uint_t ;
struct TYPE_22__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
typedef  TYPE_3__ ngx_stream_variable_value_t ;
struct TYPE_23__ {scalar_t__ offset; } ;
typedef  TYPE_4__ ngx_stream_geo_variable_value_node_t ;
struct TYPE_24__ {TYPE_3__* value; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_5__ ngx_stream_geo_range_t ;
struct TYPE_25__ {void* crc32; } ;
typedef  TYPE_6__ ngx_stream_geo_header_t ;
struct TYPE_18__ {int /*<<< orphan*/  sentinel; int /*<<< orphan*/  root; } ;
struct TYPE_21__ {TYPE_5__** low; } ;
struct TYPE_19__ {scalar_t__ len; } ;
struct TYPE_26__ {TYPE_12__ rbtree; TYPE_2__ high; TYPE_1__* pool; scalar_t__ data_size; TYPE_14__ include_name; int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_7__ ngx_stream_geo_conf_ctx_t ;
struct TYPE_27__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_8__ ngx_str_t ;
struct TYPE_28__ {scalar_t__ size; TYPE_6__* addr; int /*<<< orphan*/ * name; int /*<<< orphan*/  log; } ;
typedef  TYPE_9__ ngx_file_mapping_t ;
struct TYPE_20__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_close_file_mapping (TYPE_9__*) ; 
 int /*<<< orphan*/ * ngx_cpymem (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 void* ngx_crc32_long (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ngx_create_file_mapping (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ *,char*,TYPE_14__*) ; 
 scalar_t__ ngx_str_rbtree_lookup (TYPE_12__*,TYPE_8__*,void*) ; 
 int /*<<< orphan*/ * ngx_stream_geo_copy_values (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_geo_header ; 

__attribute__((used)) static void
ngx_stream_geo_create_binary_base(ngx_stream_geo_conf_ctx_t *ctx)
{
    u_char                                *p;
    uint32_t                               hash;
    ngx_str_t                              s;
    ngx_uint_t                             i;
    ngx_file_mapping_t                     fm;
    ngx_stream_geo_range_t                *r, *range, **ranges;
    ngx_stream_geo_header_t               *header;
    ngx_stream_geo_variable_value_node_t  *gvvn;

    fm.name = ngx_pnalloc(ctx->temp_pool, ctx->include_name.len + 5);
    if (fm.name == NULL) {
        return;
    }

    ngx_sprintf(fm.name, "%V.bin%Z", &ctx->include_name);

    fm.size = ctx->data_size;
    fm.log = ctx->pool->log;

    ngx_log_error(NGX_LOG_NOTICE, fm.log, 0,
                  "creating binary geo range base \"%s\"", fm.name);

    if (ngx_create_file_mapping(&fm) != NGX_OK) {
        return;
    }

    p = ngx_cpymem(fm.addr, &ngx_stream_geo_header,
                   sizeof(ngx_stream_geo_header_t));

    p = ngx_stream_geo_copy_values(fm.addr, p, ctx->rbtree.root,
                                   ctx->rbtree.sentinel);

    p += sizeof(ngx_stream_variable_value_t);

    ranges = (ngx_stream_geo_range_t **) p;

    p += 0x10000 * sizeof(ngx_stream_geo_range_t *);

    for (i = 0; i < 0x10000; i++) {
        r = ctx->high.low[i];
        if (r == NULL) {
            continue;
        }

        range = (ngx_stream_geo_range_t *) p;
        ranges[i] = (ngx_stream_geo_range_t *) (p - (u_char *) fm.addr);

        do {
            s.len = r->value->len;
            s.data = r->value->data;
            hash = ngx_crc32_long(s.data, s.len);
            gvvn = (ngx_stream_geo_variable_value_node_t *)
                        ngx_str_rbtree_lookup(&ctx->rbtree, &s, hash);

            range->value = (ngx_stream_variable_value_t *) gvvn->offset;
            range->start = r->start;
            range->end = r->end;
            range++;

        } while ((++r)->value);

        range->value = NULL;

        p = (u_char *) range + sizeof(void *);
    }

    header = fm.addr;
    header->crc32 = ngx_crc32_long((u_char *) fm.addr
                                       + sizeof(ngx_stream_geo_header_t),
                                   fm.size - sizeof(ngx_stream_geo_header_t));

    ngx_close_file_mapping(&fm);
}