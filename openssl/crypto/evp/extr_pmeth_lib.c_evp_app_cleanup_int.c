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

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_meth_free ; 
 int /*<<< orphan*/ * app_pkey_methods ; 
 int /*<<< orphan*/  sk_EVP_PKEY_METHOD_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void evp_app_cleanup_int(void)
{
    if (app_pkey_methods != NULL)
        sk_EVP_PKEY_METHOD_pop_free(app_pkey_methods, EVP_PKEY_meth_free);
}