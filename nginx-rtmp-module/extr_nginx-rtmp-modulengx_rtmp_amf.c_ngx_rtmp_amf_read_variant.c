#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int type; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_rtmp_amf_elt_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_amf_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  elt ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 int NGX_RTMP_AMF_TYPELESS ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_1__*,int) ; 
 scalar_t__ ngx_rtmp_amf_get (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ ngx_rtmp_amf_read (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_amf_read_variant(ngx_rtmp_amf_ctx_t *ctx, ngx_rtmp_amf_elt_t *elts,
        size_t nelts)
{
    uint8_t                 type;
    ngx_int_t               rc;
    size_t                  n;
    ngx_rtmp_amf_elt_t      elt;

    rc = ngx_rtmp_amf_get(ctx, &type, 1);
    if (rc != NGX_OK) {
        return rc;
    }

    ngx_memzero(&elt, sizeof(elt));
    for (n = 0; n < nelts; ++n, ++elts) {
        if (type == elts->type) {
            elt.data = elts->data;
            elt.len  = elts->len;
        }
    }

    elt.type = type | NGX_RTMP_AMF_TYPELESS;

    return ngx_rtmp_amf_read(ctx, &elt, 1);
}