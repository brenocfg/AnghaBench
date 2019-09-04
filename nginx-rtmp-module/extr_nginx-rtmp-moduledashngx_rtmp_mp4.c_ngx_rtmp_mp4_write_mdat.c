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
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ngx_uint_t
ngx_rtmp_mp4_write_mdat(ngx_buf_t *b, ngx_uint_t size)
{
    ngx_rtmp_mp4_field_32(b, size);

    ngx_rtmp_mp4_box(b, "mdat");

    return NGX_OK;
}