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
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_2__* secretValue; } ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ossl_cmp_asn1_octet_string_set1_bytes (TYPE_2__**,unsigned char const*,int const) ; 

int OSSL_CMP_CTX_set1_secretValue(OSSL_CMP_CTX *ctx, const unsigned char *sec,
                                  const int len)
{
    if (ctx == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }
    if (ctx->secretValue != NULL)
        OPENSSL_cleanse(ctx->secretValue->data, ctx->secretValue->length);
    return ossl_cmp_asn1_octet_string_set1_bytes(&ctx->secretValue, sec, len);
}