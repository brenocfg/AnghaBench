#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* value; void* key; } ;
typedef  TYPE_2__ ngx_table_elt_t ;
typedef  void* ngx_str_t ;
struct TYPE_9__ {int /*<<< orphan*/ * headers; } ;
typedef  TYPE_3__ ngx_mail_auth_http_conf_t ;
struct TYPE_10__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_7__ {void** elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* ngx_array_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_mail_auth_http_header(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_mail_auth_http_conf_t *ahcf = conf;

    ngx_str_t        *value;
    ngx_table_elt_t  *header;

    if (ahcf->headers == NULL) {
        ahcf->headers = ngx_array_create(cf->pool, 1, sizeof(ngx_table_elt_t));
        if (ahcf->headers == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    header = ngx_array_push(ahcf->headers);
    if (header == NULL) {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;

    header->key = value[1];
    header->value = value[2];

    return NGX_CONF_OK;
}