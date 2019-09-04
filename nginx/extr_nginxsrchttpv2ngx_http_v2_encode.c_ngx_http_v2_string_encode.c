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
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_V2_ENCODE_HUFF ; 
 int /*<<< orphan*/  NGX_HTTP_V2_ENCODE_RAW ; 
 int /*<<< orphan*/ * ngx_cpymem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t ngx_http_v2_huff_encode (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_v2_prefix (int) ; 
 int /*<<< orphan*/ * ngx_http_v2_write_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_strlow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

u_char *
ngx_http_v2_string_encode(u_char *dst, u_char *src, size_t len, u_char *tmp,
    ngx_uint_t lower)
{
    size_t  hlen;

    hlen = ngx_http_v2_huff_encode(src, len, tmp, lower);

    if (hlen > 0) {
        *dst = NGX_HTTP_V2_ENCODE_HUFF;
        dst = ngx_http_v2_write_int(dst, ngx_http_v2_prefix(7), hlen);
        return ngx_cpymem(dst, tmp, hlen);
    }

    *dst = NGX_HTTP_V2_ENCODE_RAW;
    dst = ngx_http_v2_write_int(dst, ngx_http_v2_prefix(7), len);

    if (lower) {
        ngx_strlow(dst, src, len);
        return dst + len;
    }

    return ngx_cpymem(dst, src, len);
}