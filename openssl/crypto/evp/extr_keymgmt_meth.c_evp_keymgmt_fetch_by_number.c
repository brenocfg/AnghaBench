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
typedef  int /*<<< orphan*/  EVP_KEYMGMT ;

/* Variables and functions */
 scalar_t__ EVP_KEYMGMT_free ; 
 scalar_t__ EVP_KEYMGMT_up_ref ; 
 int /*<<< orphan*/  OSSL_OP_KEYMGMT ; 
 int /*<<< orphan*/ * evp_generic_fetch_by_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int (*) (void*),void (*) (void*)) ; 
 int /*<<< orphan*/  keymgmt_from_dispatch ; 

EVP_KEYMGMT *evp_keymgmt_fetch_by_number(OPENSSL_CTX *ctx, int name_id,
                                         const char *properties)
{
    return evp_generic_fetch_by_number(ctx,
                                       OSSL_OP_KEYMGMT, name_id, properties,
                                       keymgmt_from_dispatch,
                                       (int (*)(void *))EVP_KEYMGMT_up_ref,
                                       (void (*)(void *))EVP_KEYMGMT_free);
}