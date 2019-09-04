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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_cert_add0_chain_cert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ssl_cert_add1_chain_cert(SSL *s, SSL_CTX *ctx, X509 *x)
{
    if (!ssl_cert_add0_chain_cert(s, ctx, x))
        return 0;
    X509_up_ref(x);
    return 1;
}