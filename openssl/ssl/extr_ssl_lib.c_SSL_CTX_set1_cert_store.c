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
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_set_cert_store (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_up_ref (int /*<<< orphan*/ *) ; 

void SSL_CTX_set1_cert_store(SSL_CTX *ctx, X509_STORE *store)
{
    if (store != NULL)
        X509_STORE_up_ref(store);
    SSL_CTX_set_cert_store(ctx, store);
}