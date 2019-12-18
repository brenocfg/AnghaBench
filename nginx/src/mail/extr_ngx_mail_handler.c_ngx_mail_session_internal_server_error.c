#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int quit; TYPE_2__* connection; int /*<<< orphan*/  out; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
struct TYPE_11__ {TYPE_1__* protocol; } ;
typedef  TYPE_4__ ngx_mail_core_srv_conf_t ;
struct TYPE_9__ {int /*<<< orphan*/  write; } ;
struct TYPE_8__ {int /*<<< orphan*/  internal_server_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_mail_core_module ; 
 TYPE_4__* ngx_mail_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_send (int /*<<< orphan*/ ) ; 

void
ngx_mail_session_internal_server_error(ngx_mail_session_t *s)
{
    ngx_mail_core_srv_conf_t  *cscf;

    cscf = ngx_mail_get_module_srv_conf(s, ngx_mail_core_module);

    s->out = cscf->protocol->internal_server_error;
    s->quit = 1;

    ngx_mail_send(s->connection->write);
}