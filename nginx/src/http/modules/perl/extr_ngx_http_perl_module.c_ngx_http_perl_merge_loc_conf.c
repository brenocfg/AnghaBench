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
struct TYPE_2__ {int /*<<< orphan*/  handler; int /*<<< orphan*/ * sub; } ;
typedef  TYPE_1__ ngx_http_perl_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 

__attribute__((used)) static char *
ngx_http_perl_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_perl_loc_conf_t *prev = parent;
    ngx_http_perl_loc_conf_t *conf = child;

    if (conf->sub == NULL) {
        conf->sub = prev->sub;
        conf->handler = prev->handler;
    }

    return NGX_CONF_OK;
}