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
struct TYPE_2__ {int /*<<< orphan*/  acceptex_read; int /*<<< orphan*/  post_acceptex; int /*<<< orphan*/  threads; } ;
typedef  TYPE_1__ ngx_iocp_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_conf_init_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ngx_iocp_init_conf(ngx_cycle_t *cycle, void *conf)
{
    ngx_iocp_conf_t *cf = conf;

    ngx_conf_init_value(cf->threads, 0);
    ngx_conf_init_value(cf->post_acceptex, 10);
    ngx_conf_init_value(cf->acceptex_read, 1);

    return NGX_CONF_OK;
}