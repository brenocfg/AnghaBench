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
typedef  int /*<<< orphan*/  ngx_ssl_conn_t ;
struct TYPE_5__ {TYPE_1__* ssl; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_4__ {int renegotiation; int handshake_buffer_set; scalar_t__ handshaked; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_set_write_buffer_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_SSL_BUFSIZE ; 
 int SSL_CB_ACCEPT_LOOP ; 
 int SSL_CB_HANDSHAKE_START ; 
 int /*<<< orphan*/ * SSL_get_rbio (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * SSL_get_wbio (int /*<<< orphan*/  const*) ; 
 scalar_t__ SSL_is_server (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* ngx_ssl_get_connection (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_ssl_info_callback(const ngx_ssl_conn_t *ssl_conn, int where, int ret)
{
    BIO               *rbio, *wbio;
    ngx_connection_t  *c;

#ifndef SSL_OP_NO_RENEGOTIATION

    if ((where & SSL_CB_HANDSHAKE_START)
        && SSL_is_server((ngx_ssl_conn_t *) ssl_conn))
    {
        c = ngx_ssl_get_connection((ngx_ssl_conn_t *) ssl_conn);

        if (c->ssl->handshaked) {
            c->ssl->renegotiation = 1;
            ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, 0, "SSL renegotiation");
        }
    }

#endif

    if ((where & SSL_CB_ACCEPT_LOOP) == SSL_CB_ACCEPT_LOOP) {
        c = ngx_ssl_get_connection((ngx_ssl_conn_t *) ssl_conn);

        if (!c->ssl->handshake_buffer_set) {
            /*
             * By default OpenSSL uses 4k buffer during a handshake,
             * which is too low for long certificate chains and might
             * result in extra round-trips.
             *
             * To adjust a buffer size we detect that buffering was added
             * to write side of the connection by comparing rbio and wbio.
             * If they are different, we assume that it's due to buffering
             * added to wbio, and set buffer size.
             */

            rbio = SSL_get_rbio(ssl_conn);
            wbio = SSL_get_wbio(ssl_conn);

            if (rbio != wbio) {
                (void) BIO_set_write_buffer_size(wbio, NGX_SSL_BUFSIZE);
                c->ssl->handshake_buffer_set = 1;
            }
        }
    }
}