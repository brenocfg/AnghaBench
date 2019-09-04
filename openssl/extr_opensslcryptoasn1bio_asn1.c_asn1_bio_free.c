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
struct TYPE_4__ {struct TYPE_4__* buf; } ;
typedef  TYPE_1__ BIO_ASN1_BUF_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static int asn1_bio_free(BIO *b)
{
    BIO_ASN1_BUF_CTX *ctx;

    if (b == NULL)
        return 0;

    ctx = BIO_get_data(b);
    if (ctx == NULL)
        return 0;

    OPENSSL_free(ctx->buf);
    OPENSSL_free(ctx);
    BIO_set_data(b, NULL);
    BIO_set_init(b, 0);

    return 1;
}