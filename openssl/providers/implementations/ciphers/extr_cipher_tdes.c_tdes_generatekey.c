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
struct TYPE_3__ {size_t keylen; int /*<<< orphan*/  libctx; } ;
typedef  TYPE_1__ PROV_CIPHER_CTX ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_set_odd_parity (int /*<<< orphan*/ *) ; 
 scalar_t__ rand_priv_bytes_ex (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int tdes_generatekey(PROV_CIPHER_CTX *ctx, void *ptr)
{

    DES_cblock *deskey = ptr;
    size_t kl = ctx->keylen;

    if (kl == 0 || rand_priv_bytes_ex(ctx->libctx, ptr, kl) <= 0)
        return 0;
    DES_set_odd_parity(deskey);
    if (kl >= 16)
        DES_set_odd_parity(deskey + 1);
    if (kl >= 24) {
        DES_set_odd_parity(deskey + 2);
        return 1;
    }
    return 0;
}