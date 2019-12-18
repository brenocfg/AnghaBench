#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_ssl_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/  log; TYPE_1__* ssl; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_4__ {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ SSL_set_session (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_ssl_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ngx_int_t
ngx_ssl_set_session(ngx_connection_t *c, ngx_ssl_session_t *session)
{
    if (session) {
        if (SSL_set_session(c->ssl->connection, session) == 0) {
            ngx_ssl_error(NGX_LOG_ALERT, c->log, 0, "SSL_set_session() failed");
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}