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

/* Variables and functions */

int
ngx_http_lua_ffi_sha1_bin(const u_char *src, size_t len, u_char *dst)
{
#if (NGX_HAVE_SHA1)
    ngx_sha1_t               sha;

    ngx_sha1_init(&sha);
    ngx_sha1_update(&sha, src, len);
    ngx_sha1_final(dst, &sha);

    return 1;
#else
    return 0;
#endif
}