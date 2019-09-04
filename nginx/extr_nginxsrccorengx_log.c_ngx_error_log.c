#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_6__ {TYPE_1__* cycle; } ;
typedef  TYPE_2__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_5__ {int /*<<< orphan*/  new_log; } ;

/* Variables and functions */
 char* ngx_log_set_log (TYPE_2__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static char *
ngx_error_log(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_log_t  *dummy;

    dummy = &cf->cycle->new_log;

    return ngx_log_set_log(cf, &dummy);
}