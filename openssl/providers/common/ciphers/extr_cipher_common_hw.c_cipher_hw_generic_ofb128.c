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
struct TYPE_3__ {int num; int /*<<< orphan*/  block; int /*<<< orphan*/  iv; int /*<<< orphan*/  ks; } ;
typedef  TYPE_1__ PROV_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ofb128_encrypt (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int cipher_hw_generic_ofb128(PROV_CIPHER_CTX *dat, unsigned char *out,
                             const unsigned char *in, size_t len)
{
    int num = dat->num;

    CRYPTO_ofb128_encrypt(in, out, len, dat->ks, dat->iv, &num, dat->block);
    dat->num = num;

    return 1;
}