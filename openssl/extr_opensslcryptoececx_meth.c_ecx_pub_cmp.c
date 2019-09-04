#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pubkey; } ;
struct TYPE_7__ {TYPE_3__* ecx; } ;
struct TYPE_8__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  TYPE_3__ ECX_KEY ;

/* Variables and functions */
 scalar_t__ CRYPTO_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYLEN (TYPE_2__ const*) ; 

__attribute__((used)) static int ecx_pub_cmp(const EVP_PKEY *a, const EVP_PKEY *b)
{
    const ECX_KEY *akey = a->pkey.ecx;
    const ECX_KEY *bkey = b->pkey.ecx;

    if (akey == NULL || bkey == NULL)
        return -2;

    return CRYPTO_memcmp(akey->pubkey, bkey->pubkey, KEYLEN(a)) == 0;
}