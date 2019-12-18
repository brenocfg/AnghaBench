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
typedef  int /*<<< orphan*/  X509_STORE_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_CTX_cleanup (int /*<<< orphan*/ *) ; 

void X509_STORE_CTX_free(X509_STORE_CTX *ctx)
{
    if (ctx == NULL)
        return;

    X509_STORE_CTX_cleanup(ctx);
    OPENSSL_free(ctx);
}