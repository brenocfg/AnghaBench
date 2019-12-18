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
typedef  int /*<<< orphan*/  EVP_MAC ;

/* Variables and functions */
 int /*<<< orphan*/  OSSL_OP_MAC ; 
 int /*<<< orphan*/ * evp_generic_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evp_mac_free ; 
 int /*<<< orphan*/  evp_mac_from_dispatch ; 
 int /*<<< orphan*/  evp_mac_up_ref ; 

EVP_MAC *EVP_MAC_fetch(OPENSSL_CTX *libctx, const char *algorithm,
                       const char *properties)
{
    return evp_generic_fetch(libctx, OSSL_OP_MAC, algorithm, properties,
                             evp_mac_from_dispatch, evp_mac_up_ref,
                             evp_mac_free);
}