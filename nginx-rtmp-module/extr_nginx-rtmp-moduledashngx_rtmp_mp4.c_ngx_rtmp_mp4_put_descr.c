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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_8 (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_put_descr(ngx_buf_t *b, int tag, size_t size)
{
    ngx_rtmp_mp4_field_8(b, (uint8_t) tag);
    ngx_rtmp_mp4_field_8(b, size & 0x7F);

    return NGX_OK;
}