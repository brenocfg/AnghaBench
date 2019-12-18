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
struct cmac_data_st {int /*<<< orphan*/  cipher; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int CMAC_Init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_prov_cipher_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_prov_cipher_engine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_prov_cipher_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmac_init(void *vmacctx)
{
    struct cmac_data_st *macctx = vmacctx;
    int rv = CMAC_Init(macctx->ctx, NULL, 0,
                       ossl_prov_cipher_cipher(&macctx->cipher),
                       ossl_prov_cipher_engine(&macctx->cipher));

    ossl_prov_cipher_reset(&macctx->cipher);
    return rv;
}