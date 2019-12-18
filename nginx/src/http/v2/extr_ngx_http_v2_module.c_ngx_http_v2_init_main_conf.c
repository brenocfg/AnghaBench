#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  recv_buffer_size; } ;
typedef  TYPE_1__ ngx_http_v2_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_conf_init_size_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ngx_http_v2_init_main_conf(ngx_conf_t *cf, void *conf)
{
    ngx_http_v2_main_conf_t *h2mcf = conf;

    ngx_conf_init_size_value(h2mcf->recv_buffer_size, 256 * 1024);

    return NGX_CONF_OK;
}