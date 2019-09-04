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
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int NGX_HTTP_V2_STATE_BUFFER_SIZE ; 

__attribute__((used)) static char *
ngx_http_v2_recv_buffer_size(ngx_conf_t *cf, void *post, void *data)
{
    size_t *sp = data;

    if (*sp <= 2 * NGX_HTTP_V2_STATE_BUFFER_SIZE) {
        return "value is too small";
    }

    return NGX_CONF_OK;
}