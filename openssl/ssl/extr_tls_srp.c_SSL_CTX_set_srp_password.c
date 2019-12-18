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
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTRL_SET_TLS_EXT_SRP_PASSWORD ; 
 int tls1_ctx_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int SSL_CTX_set_srp_password(SSL_CTX *ctx, char *password)
{
    return tls1_ctx_ctrl(ctx, SSL_CTRL_SET_TLS_EXT_SRP_PASSWORD, 0, password);
}