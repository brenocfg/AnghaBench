#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ks3; int /*<<< orphan*/  ks2; int /*<<< orphan*/  ks1; } ;
typedef  TYPE_1__ PROV_TDES_CTX ;
typedef  int /*<<< orphan*/  PROV_CIPHER_CTX ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_set_key_unchecked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 

__attribute__((used)) static int cipher_hw_desx_cbc_initkey(PROV_CIPHER_CTX *ctx,
                                      const unsigned char *key, size_t keylen)
{
    PROV_TDES_CTX *tctx = (PROV_TDES_CTX *)ctx;
    DES_cblock *deskey = (DES_cblock *)key;

    DES_set_key_unchecked(deskey, &tctx->ks1);
    memcpy(&tctx->ks2, &key[8], 8);
    memcpy(&tctx->ks3, &key[16], 8);

    return 1;
}