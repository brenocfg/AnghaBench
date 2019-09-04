#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_short ;
typedef  size_t ngx_uint_t ;
struct TYPE_12__ {int /*<<< orphan*/  value; void* end; void* start; } ;
typedef  TYPE_2__ ngx_stream_geo_range_t ;
struct TYPE_11__ {TYPE_2__** low; } ;
struct TYPE_13__ {int /*<<< orphan*/  value; int /*<<< orphan*/  net; TYPE_1__ high; int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_3__ ngx_stream_geo_conf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
struct TYPE_14__ {size_t nelts; TYPE_2__* elts; } ;
typedef  TYPE_4__ ngx_array_t ;
typedef  int in_addr_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 TYPE_4__* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* ngx_array_push (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t,...) ; 
 int /*<<< orphan*/  ngx_memmove (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static char *
ngx_stream_geo_add_range(ngx_conf_t *cf, ngx_stream_geo_conf_ctx_t *ctx,
    in_addr_t start, in_addr_t end)
{
    in_addr_t                n;
    ngx_uint_t               h, i, s, e;
    ngx_array_t             *a;
    ngx_stream_geo_range_t  *range;

    for (n = start; n <= end; n = (n + 0x10000) & 0xffff0000) {

        h = n >> 16;

        if (n == start) {
            s = n & 0xffff;
        } else {
            s = 0;
        }

        if ((n | 0xffff) > end) {
            e = end & 0xffff;

        } else {
            e = 0xffff;
        }

        a = (ngx_array_t *) ctx->high.low[h];

        if (a == NULL) {
            a = ngx_array_create(ctx->temp_pool, 64,
                                 sizeof(ngx_stream_geo_range_t));
            if (a == NULL) {
                return NGX_CONF_ERROR;
            }

            ctx->high.low[h] = (ngx_stream_geo_range_t *) a;
        }

        i = a->nelts;
        range = a->elts;

        while (i) {

            i--;

            if (e < (ngx_uint_t) range[i].start) {
                continue;
            }

            if (s > (ngx_uint_t) range[i].end) {

                /* add after the range */

                range = ngx_array_push(a);
                if (range == NULL) {
                    return NGX_CONF_ERROR;
                }

                range = a->elts;

                ngx_memmove(&range[i + 2], &range[i + 1],
                           (a->nelts - 2 - i) * sizeof(ngx_stream_geo_range_t));

                range[i + 1].start = (u_short) s;
                range[i + 1].end = (u_short) e;
                range[i + 1].value = ctx->value;

                goto next;
            }

            if (s == (ngx_uint_t) range[i].start
                && e == (ngx_uint_t) range[i].end)
            {
                ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                    "duplicate range \"%V\", value: \"%v\", old value: \"%v\"",
                    ctx->net, ctx->value, range[i].value);

                range[i].value = ctx->value;

                goto next;
            }

            if (s > (ngx_uint_t) range[i].start
                && e < (ngx_uint_t) range[i].end)
            {
                /* split the range and insert the new one */

                range = ngx_array_push(a);
                if (range == NULL) {
                    return NGX_CONF_ERROR;
                }

                range = ngx_array_push(a);
                if (range == NULL) {
                    return NGX_CONF_ERROR;
                }

                range = a->elts;

                ngx_memmove(&range[i + 3], &range[i + 1],
                           (a->nelts - 3 - i) * sizeof(ngx_stream_geo_range_t));

                range[i + 2].start = (u_short) (e + 1);
                range[i + 2].end = range[i].end;
                range[i + 2].value = range[i].value;

                range[i + 1].start = (u_short) s;
                range[i + 1].end = (u_short) e;
                range[i + 1].value = ctx->value;

                range[i].end = (u_short) (s - 1);

                goto next;
            }

            if (s == (ngx_uint_t) range[i].start
                && e < (ngx_uint_t) range[i].end)
            {
                /* shift the range start and insert the new range */

                range = ngx_array_push(a);
                if (range == NULL) {
                    return NGX_CONF_ERROR;
                }

                range = a->elts;

                ngx_memmove(&range[i + 1], &range[i],
                           (a->nelts - 1 - i) * sizeof(ngx_stream_geo_range_t));

                range[i + 1].start = (u_short) (e + 1);

                range[i].start = (u_short) s;
                range[i].end = (u_short) e;
                range[i].value = ctx->value;

                goto next;
            }

            if (s > (ngx_uint_t) range[i].start
                && e == (ngx_uint_t) range[i].end)
            {
                /* shift the range end and insert the new range */

                range = ngx_array_push(a);
                if (range == NULL) {
                    return NGX_CONF_ERROR;
                }

                range = a->elts;

                ngx_memmove(&range[i + 2], &range[i + 1],
                           (a->nelts - 2 - i) * sizeof(ngx_stream_geo_range_t));

                range[i + 1].start = (u_short) s;
                range[i + 1].end = (u_short) e;
                range[i + 1].value = ctx->value;

                range[i].end = (u_short) (s - 1);

                goto next;
            }

            s = (ngx_uint_t) range[i].start;
            e = (ngx_uint_t) range[i].end;

            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                         "range \"%V\" overlaps \"%d.%d.%d.%d-%d.%d.%d.%d\"",
                         ctx->net,
                         h >> 8, h & 0xff, s >> 8, s & 0xff,
                         h >> 8, h & 0xff, e >> 8, e & 0xff);

            return NGX_CONF_ERROR;
        }

        /* add the first range */

        range = ngx_array_push(a);
        if (range == NULL) {
            return NGX_CONF_ERROR;
        }

        range = a->elts;

        ngx_memmove(&range[1], &range[0],
                    (a->nelts - 1) * sizeof(ngx_stream_geo_range_t));

        range[0].start = (u_short) s;
        range[0].end = (u_short) e;
        range[0].value = ctx->value;

    next:

        if (h == 0xffff) {
            break;
        }
    }

    return NGX_CONF_OK;
}