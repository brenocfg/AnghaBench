#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RTMP ;

/* Variables and functions */
 int FALSE ; 

int
RTMP_TLS_Accept(RTMP *r, void *ctx)
{
#if defined(CRYPTO) && !defined(NO_SSL)
    tls_server_ctx *srv_ctx = ctx;
    TLS_server(srv_ctx, r->m_sb.sb_ssl);

#if defined(USE_MBEDTLS)
    mbedtls_net_context *client_fd = &RTMP_TLS_ctx->net;
    mbedtls_net_init(client_fd);
    client_fd->fd = r->m_sb.sb_socket;
    TLS_setfd(r->m_sb.sb_ssl, client_fd);
#else
    TLS_setfd(r->m_sb.sb_ssl, r->m_sb.sb_socket);
#endif

    int connect_return = TLS_connect(r->m_sb.sb_ssl);
    if (connect_return < 0)
    {
        RTMP_Log(RTMP_LOGERROR, "%s, TLS_Connect failed", __FUNCTION__);
        return FALSE;
    }
    return TRUE;
#else
    (void)r;
    (void)ctx;
    return FALSE;
#endif
}