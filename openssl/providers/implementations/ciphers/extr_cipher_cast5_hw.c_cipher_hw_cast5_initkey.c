#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ks; } ;
struct TYPE_4__ {TYPE_1__ ks; } ;
typedef  int /*<<< orphan*/  PROV_CIPHER_CTX ;
typedef  TYPE_2__ PROV_CAST_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_set_key (int /*<<< orphan*/ *,size_t,unsigned char const*) ; 

__attribute__((used)) static int cipher_hw_cast5_initkey(PROV_CIPHER_CTX *ctx,
                                   const unsigned char *key, size_t keylen)
{
    PROV_CAST_CTX *bctx =  (PROV_CAST_CTX *)ctx;

    CAST_set_key(&(bctx->ks.ks), keylen, key);
    return 1;
}