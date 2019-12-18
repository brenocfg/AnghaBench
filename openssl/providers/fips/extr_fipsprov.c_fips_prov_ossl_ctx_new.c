#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  void FIPS_GLOBAL ;

/* Variables and functions */
 void* OPENSSL_zalloc (int) ; 

__attribute__((used)) static void *fips_prov_ossl_ctx_new(OPENSSL_CTX *libctx)
{
    FIPS_GLOBAL *fgbl = OPENSSL_zalloc(sizeof(*fgbl));

    return fgbl;
}