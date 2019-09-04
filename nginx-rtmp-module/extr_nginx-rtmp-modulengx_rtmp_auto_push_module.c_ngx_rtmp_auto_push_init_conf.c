#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {TYPE_2__ socket_dir; int /*<<< orphan*/  push_reconnect; int /*<<< orphan*/  auto_push; } ;
typedef  TYPE_1__ ngx_rtmp_auto_push_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_conf_init_msec_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_init_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_2__*,char*) ; 

__attribute__((used)) static char *
ngx_rtmp_auto_push_init_conf(ngx_cycle_t *cycle, void *conf)
{
    ngx_rtmp_auto_push_conf_t      *apcf = conf;

    ngx_conf_init_value(apcf->auto_push, 0);
    ngx_conf_init_msec_value(apcf->push_reconnect, 100);

    if (apcf->socket_dir.len == 0) {
        ngx_str_set(&apcf->socket_dir, "/tmp");
    }

    return NGX_CONF_OK;
}