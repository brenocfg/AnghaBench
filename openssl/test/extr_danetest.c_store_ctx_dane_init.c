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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_get0_dane (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_CTX_set0_dane (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void store_ctx_dane_init(X509_STORE_CTX *store_ctx, SSL *ssl)
{
    X509_STORE_CTX_set0_dane(store_ctx, SSL_get0_dane(ssl));
}