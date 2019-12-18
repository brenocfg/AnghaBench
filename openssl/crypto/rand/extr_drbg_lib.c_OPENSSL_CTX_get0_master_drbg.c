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
struct TYPE_3__ {int /*<<< orphan*/ * master_drbg; } ;
typedef  int /*<<< orphan*/  RAND_DRBG ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_1__ DRBG_GLOBAL ;

/* Variables and functions */
 TYPE_1__* drbg_get_global (int /*<<< orphan*/ *) ; 

RAND_DRBG *OPENSSL_CTX_get0_master_drbg(OPENSSL_CTX *ctx)
{
    DRBG_GLOBAL *dgbl = drbg_get_global(ctx);

    if (dgbl == NULL)
        return NULL;

    return dgbl->master_drbg;
}