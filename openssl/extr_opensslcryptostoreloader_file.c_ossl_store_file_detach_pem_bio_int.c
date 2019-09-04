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
typedef  int /*<<< orphan*/  OSSL_STORE_LOADER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_STORE_LOADER_CTX_free (int /*<<< orphan*/ *) ; 

int ossl_store_file_detach_pem_bio_int(OSSL_STORE_LOADER_CTX *ctx)
{
    OSSL_STORE_LOADER_CTX_free(ctx);
    return 1;
}