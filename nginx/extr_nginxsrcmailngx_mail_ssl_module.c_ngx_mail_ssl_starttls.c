#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int enable; int /*<<< orphan*/  line; int /*<<< orphan*/  file; int /*<<< orphan*/  listen; scalar_t__ starttls; } ;
typedef  TYPE_4__ ngx_mail_ssl_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_13__ {TYPE_3__* conf_file; } ;
typedef  TYPE_5__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__ name; } ;
struct TYPE_11__ {int /*<<< orphan*/  line; TYPE_2__ file; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_MAIL_STARTTLS_OFF ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 char* ngx_conf_set_enum_slot (TYPE_5__*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static char *
ngx_mail_ssl_starttls(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_mail_ssl_conf_t  *scf = conf;

    char  *rv;

    rv = ngx_conf_set_enum_slot(cf, cmd, conf);

    if (rv != NGX_CONF_OK) {
        return rv;
    }

    if (scf->enable == 1 && (ngx_int_t) scf->starttls > NGX_MAIL_STARTTLS_OFF) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "\"ssl\" directive conflicts with \"starttls\"");
        return NGX_CONF_ERROR;
    }

    if (!scf->listen) {
        scf->file = cf->conf_file->file.name.data;
        scf->line = cf->conf_file->line;
    }

    return NGX_CONF_OK;
}