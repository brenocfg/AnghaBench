#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bufsize; int /*<<< orphan*/  state; int /*<<< orphan*/  asn1_tag; int /*<<< orphan*/  asn1_class; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ BIO_ASN1_BUF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_BIO_INIT ; 
 int /*<<< orphan*/  ASN1_STATE_START ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/  V_ASN1_UNIVERSAL ; 

__attribute__((used)) static int asn1_bio_init(BIO_ASN1_BUF_CTX *ctx, int size)
{
    if ((ctx->buf = OPENSSL_malloc(size)) == NULL) {
        ASN1err(ASN1_F_ASN1_BIO_INIT, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    ctx->bufsize = size;
    ctx->asn1_class = V_ASN1_UNIVERSAL;
    ctx->asn1_tag = V_ASN1_OCTET_STRING;
    ctx->state = ASN1_STATE_START;
    return 1;
}