#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fetched_cipher; int /*<<< orphan*/  tag; int /*<<< orphan*/ * aad; int /*<<< orphan*/  plaintext; int /*<<< orphan*/  ciphertext; int /*<<< orphan*/  iv; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  TYPE_2__ CIPHER_DATA ;

/* Variables and functions */
 int AAD_NUM ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cipher_test_cleanup(EVP_TEST *t)
{
    int i;
    CIPHER_DATA *cdat = t->data;

    OPENSSL_free(cdat->key);
    OPENSSL_free(cdat->iv);
    OPENSSL_free(cdat->ciphertext);
    OPENSSL_free(cdat->plaintext);
    for (i = 0; i < AAD_NUM; i++)
        OPENSSL_free(cdat->aad[i]);
    OPENSSL_free(cdat->tag);
    EVP_CIPHER_meth_free(cdat->fetched_cipher);
}