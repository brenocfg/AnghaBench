#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* pkey; } ;
struct TYPE_7__ {int /*<<< orphan*/  pubkey; } ;
struct TYPE_5__ {TYPE_3__* ecx; } ;
struct TYPE_6__ {TYPE_1__ pkey; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  TYPE_3__ ECX_KEY ;

/* Variables and functions */
 size_t ED25519_SIGSIZE ; 
 int ED25519_verify (unsigned char const*,size_t,unsigned char const*,int /*<<< orphan*/ ) ; 
 TYPE_4__* EVP_MD_CTX_pkey_ctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_ecd_digestverify25519(EVP_MD_CTX *ctx, const unsigned char *sig,
                                      size_t siglen, const unsigned char *tbs,
                                      size_t tbslen)
{
    const ECX_KEY *edkey = EVP_MD_CTX_pkey_ctx(ctx)->pkey->pkey.ecx;

    if (siglen != ED25519_SIGSIZE)
        return 0;

    return ED25519_verify(tbs, tbslen, sig, edkey->pubkey);
}