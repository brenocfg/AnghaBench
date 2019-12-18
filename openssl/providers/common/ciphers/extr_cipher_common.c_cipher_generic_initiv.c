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
struct TYPE_3__ {size_t ivlen; int iv_set; int /*<<< orphan*/  oiv; int /*<<< orphan*/  iv; } ;
typedef  TYPE_1__ PROV_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_INVALID_IVLEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

int cipher_generic_initiv(PROV_CIPHER_CTX *ctx, const unsigned char *iv,
                          size_t ivlen)
{
    if (ivlen != ctx->ivlen
        || ivlen > sizeof(ctx->iv)) {
        ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_IVLEN);
        return 0;
    }
    ctx->iv_set = 1;
    memcpy(ctx->iv, iv, ivlen);
    memcpy(ctx->oiv, iv, ivlen);
    return 1;
}