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
typedef  int /*<<< orphan*/  DRBG_GLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_CTX_DRBG_INDEX ; 
 int /*<<< orphan*/  drbg_ossl_ctx_method ; 
 int /*<<< orphan*/ * openssl_ctx_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static DRBG_GLOBAL *drbg_get_global(OPENSSL_CTX *libctx)
{
    return openssl_ctx_get_data(libctx, OPENSSL_CTX_DRBG_INDEX,
                                &drbg_ossl_ctx_method);
}