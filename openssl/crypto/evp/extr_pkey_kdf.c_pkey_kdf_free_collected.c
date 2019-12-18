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
struct TYPE_3__ {int /*<<< orphan*/ * collected_info; int /*<<< orphan*/ * collected_seed; } ;
typedef  TYPE_1__ EVP_PKEY_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkey_kdf_free_collected(EVP_PKEY_KDF_CTX *pkctx)
{
    BUF_MEM_free(pkctx->collected_seed);
    pkctx->collected_seed = NULL;
    BUF_MEM_free(pkctx->collected_info);
    pkctx->collected_info = NULL;
}