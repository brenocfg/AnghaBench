#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ssl_ctx; scalar_t__ extra_len; int /*<<< orphan*/ * extra_buf; int /*<<< orphan*/ * ssl_buf; scalar_t__ peek_len; int /*<<< orphan*/ * peek_msg; int /*<<< orphan*/ * peek_msg_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteSecurityContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  FreeCredentialsHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ SecIsValidHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCP_CLOSE (int) ; 
 int /*<<< orphan*/  compat_cred_handle ; 
 int /*<<< orphan*/  cred_handle ; 
 scalar_t__ cred_handle_initialized ; 
 int g_sock ; 
 TYPE_1__* g_ssl ; 
 int /*<<< orphan*/  g_ssl_initialized ; 
 int /*<<< orphan*/ * g_ssl_server ; 
 scalar_t__ have_compat_cred_handle ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

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