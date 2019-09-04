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
typedef  int /*<<< orphan*/  ngx_ssl_session_t ;
typedef  int /*<<< orphan*/  ngx_ssl_conn_t ;
struct TYPE_6__ {TYPE_1__* ssl; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_5__ {int /*<<< orphan*/ * session; int /*<<< orphan*/  (* save_session ) (TYPE_2__*) ;} ;

/* Variables and functions */
 TYPE_2__* ngx_ssl_get_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int
ngx_ssl_new_client_session(ngx_ssl_conn_t *ssl_conn, ngx_ssl_session_t *sess)
{
    ngx_connection_t  *c;

    c = ngx_ssl_get_connection(ssl_conn);

    if (c->ssl->save_session) {
        c->ssl->session = sess;

        c->ssl->save_session(c);

        c->ssl->session = NULL;
    }

    return 0;
}