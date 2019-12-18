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
typedef  int /*<<< orphan*/  OSSL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_KDF_PARAM_SIZE ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int OSSL_PARAM_set_size_t (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_MAX ; 

__attribute__((used)) static int kbkdf_get_ctx_params(void *vctx, OSSL_PARAM params[])
{
    OSSL_PARAM *p;

    p = OSSL_PARAM_locate(params, OSSL_KDF_PARAM_SIZE);
    if (p == NULL)
        return -2;

    /* KBKDF can produce results as large as you like. */
    return OSSL_PARAM_set_size_t(p, SIZE_MAX);
}