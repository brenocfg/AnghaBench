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
struct TYPE_3__ {int /*<<< orphan*/  iv; } ;
typedef  TYPE_1__ PROV_CCM_CTX ;

/* Variables and functions */
 size_t EVP_CCM_TLS_FIXED_IV_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static int ccm_tls_iv_set_fixed(PROV_CCM_CTX *ctx, unsigned char *fixed,
                                size_t flen)
{
    if (flen != EVP_CCM_TLS_FIXED_IV_LEN)
        return 0;

    /* Copy to first part of the iv. */
    memcpy(ctx->iv, fixed, flen);
    return 1;
}