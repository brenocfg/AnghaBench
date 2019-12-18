#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  chain; int /*<<< orphan*/  key; int /*<<< orphan*/  cert; } ;
typedef  TYPE_1__ SSL_EXCERT ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 

void ssl_excert_free(SSL_EXCERT *exc)
{
    SSL_EXCERT *curr;

    if (exc == NULL)
        return;
    while (exc) {
        X509_free(exc->cert);
        EVP_PKEY_free(exc->key);
        sk_X509_pop_free(exc->chain, X509_free);
        curr = exc;
        exc = exc->next;
        OPENSSL_free(curr);
    }
}