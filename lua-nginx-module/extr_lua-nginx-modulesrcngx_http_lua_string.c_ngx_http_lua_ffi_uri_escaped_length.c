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
 int /*<<< orphan*/  NGX_ESCAPE_URI_COMPONENT ; 
 int ngx_http_lua_escape_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

size_t
ngx_http_lua_ffi_uri_escaped_length(const u_char *src, size_t len)
{
    return len + 2 * ngx_http_lua_escape_uri(NULL, (u_char *) src, len,
                                             NGX_ESCAPE_URI_COMPONENT);
}