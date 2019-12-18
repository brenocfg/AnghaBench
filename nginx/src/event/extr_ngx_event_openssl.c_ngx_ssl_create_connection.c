#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_8__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_1__ ngx_ssl_t ;
struct TYPE_9__ {int buffer; int try_early_data; int /*<<< orphan*/ * connection; int /*<<< orphan*/  session_ctx; int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_2__ ngx_ssl_connection_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {TYPE_2__* ssl; int /*<<< orphan*/  log; int /*<<< orphan*/  fd; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_SSL_BUFFER ; 
 int NGX_SSL_CLIENT ; 
 scalar_t__ SSL_CTX_get_max_early_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_OP_NO_RENEGOTIATION ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_accept_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ SSL_set_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_ssl_connection_index ; 
 int /*<<< orphan*/  ngx_ssl_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ngx_int_t
ngx_ssl_create_connection(ngx_ssl_t *ssl, ngx_connection_t *c, ngx_uint_t flags)
{
    ngx_ssl_connection_t  *sc;

    sc = ngx_pcalloc(c->pool, sizeof(ngx_ssl_connection_t));
    if (sc == NULL) {
        return NGX_ERROR;
    }

    sc->buffer = ((flags & NGX_SSL_BUFFER) != 0);
    sc->buffer_size = ssl->buffer_size;

    sc->session_ctx = ssl->ctx;

#ifdef SSL_READ_EARLY_DATA_SUCCESS
    if (SSL_CTX_get_max_early_data(ssl->ctx)) {
        sc->try_early_data = 1;
    }
#endif

    sc->connection = SSL_new(ssl->ctx);

    if (sc->connection == NULL) {
        ngx_ssl_error(NGX_LOG_ALERT, c->log, 0, "SSL_new() failed");
        return NGX_ERROR;
    }

    if (SSL_set_fd(sc->connection, c->fd) == 0) {
        ngx_ssl_error(NGX_LOG_ALERT, c->log, 0, "SSL_set_fd() failed");
        return NGX_ERROR;
    }

    if (flags & NGX_SSL_CLIENT) {
        SSL_set_connect_state(sc->connection);

    } else {
        SSL_set_accept_state(sc->connection);

#ifdef SSL_OP_NO_RENEGOTIATION
        SSL_set_options(sc->connection, SSL_OP_NO_RENEGOTIATION);
#endif
    }

    if (SSL_set_ex_data(sc->connection, ngx_ssl_connection_index, c) == 0) {
        ngx_ssl_error(NGX_LOG_ALERT, c->log, 0, "SSL_set_ex_data() failed");
        return NGX_ERROR;
    }

    c->ssl = sc;

    return NGX_OK;
}