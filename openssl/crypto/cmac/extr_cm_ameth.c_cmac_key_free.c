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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  int /*<<< orphan*/  EVP_MAC ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MAC_CTX_mac (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cmac_key_free(EVP_PKEY *pkey)
{
    EVP_MAC_CTX *cmctx = EVP_PKEY_get0(pkey);
    EVP_MAC *mac = cmctx == NULL ? NULL : EVP_MAC_CTX_mac(cmctx);

    EVP_MAC_CTX_free(cmctx);
    EVP_MAC_free(mac);
}