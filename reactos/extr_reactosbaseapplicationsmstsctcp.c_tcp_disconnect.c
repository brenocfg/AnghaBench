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

/* Variables and functions */
 int /*<<< orphan*/  TCP_CLOSE (int) ; 
 int g_sock ; 

void
tcp_disconnect(void)
{
#ifdef WITH_SSL
	if (g_ssl)
	{
		xfree(g_ssl->peek_msg_mem);
		g_ssl->peek_msg_mem = NULL;
		g_ssl->peek_msg = NULL;
		g_ssl->peek_len = 0;
		xfree(g_ssl->ssl_buf);
		g_ssl->ssl_buf = NULL;
		xfree(g_ssl->extra_buf);
		g_ssl->extra_buf = NULL;
		g_ssl->extra_len = 0;
		if (SecIsValidHandle(&g_ssl->ssl_ctx))
			DeleteSecurityContext(&g_ssl->ssl_ctx);
		if (cred_handle_initialized)
			FreeCredentialsHandle(&cred_handle);
		if (have_compat_cred_handle)
			FreeCredentialsHandle(&compat_cred_handle);
		if (g_ssl_server)
		{
			xfree(g_ssl_server);
			g_ssl_server = NULL;
		}
		g_ssl = NULL;
		g_ssl_initialized = False;
	}
#endif /* WITH_SSL */
	TCP_CLOSE(g_sock);
	g_sock = -1;
}