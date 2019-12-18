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
typedef  char u_char ;
typedef  int /*<<< orphan*/  ngx_md5_t ;

/* Variables and functions */
 char* ngx_hex_dump (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_md5_final (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_md5_update (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  ngx_min (size_t,int) ; 

__attribute__((used)) static void
ngx_rtmp_notify_set_name(u_char *dst, size_t dst_len, u_char *src,
    size_t src_len)
{
    u_char     result[16], *p;
    ngx_md5_t  md5;

    ngx_md5_init(&md5);
    ngx_md5_update(&md5, src, src_len);
    ngx_md5_final(result, &md5);

    p = ngx_hex_dump(dst, result, ngx_min((dst_len - 1) / 2, 16));
    *p = '\0';
}