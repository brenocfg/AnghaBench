#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_rtmp_amf_elt_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_amf_ctx_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_rtmp_amf_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_rtmp_amf_reverse_copy (int /*<<< orphan*/ *,size_t*,int) ; 
 scalar_t__ ngx_rtmp_amf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_amf_write_array(ngx_rtmp_amf_ctx_t *ctx,
        ngx_rtmp_amf_elt_t *elts, size_t nelts)
{
    uint32_t                len;
    size_t                  n;
    u_char                  buf[4];

    len = nelts;
    if (ngx_rtmp_amf_put(ctx,
                ngx_rtmp_amf_reverse_copy(buf,
                    &len, 4), 4) != NGX_OK)
    {
        return NGX_ERROR;
    }

    for(n = 0; n < nelts; ++n) {
        if (ngx_rtmp_amf_write(ctx, &elts[n], 1) != NGX_OK) {
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}