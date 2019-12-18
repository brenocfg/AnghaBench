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
struct TYPE_4__ {int /*<<< orphan*/  cipher; } ;
typedef  TYPE_1__ BIO_ENC_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (TYPE_1__*,int) ; 

__attribute__((used)) static int enc_free(BIO *a)
{
    BIO_ENC_CTX *b;

    if (a == NULL)
        return 0;

    b = BIO_get_data(a);
    if (b == NULL)
        return 0;

    EVP_CIPHER_CTX_free(b->cipher);
    OPENSSL_clear_free(b, sizeof(BIO_ENC_CTX));
    BIO_set_data(a, NULL);
    BIO_set_init(a, 0);

    return 1;
}