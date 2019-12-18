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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set_mac_key (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 scalar_t__ EVP_PKEY_keygen (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ EVP_PKEY_keygen_init (int /*<<< orphan*/ *) ; 

EVP_PKEY *EVP_PKEY_new_mac_key(int type, ENGINE *e,
                               const unsigned char *key, int keylen)
{
    EVP_PKEY_CTX *mac_ctx = NULL;
    EVP_PKEY *mac_key = NULL;
    mac_ctx = EVP_PKEY_CTX_new_id(type, e);
    if (!mac_ctx)
        return NULL;
    if (EVP_PKEY_keygen_init(mac_ctx) <= 0)
        goto merr;
    if (EVP_PKEY_CTX_set_mac_key(mac_ctx, key, keylen) <= 0)
        goto merr;
    if (EVP_PKEY_keygen(mac_ctx, &mac_key) <= 0)
        goto merr;
 merr:
    EVP_PKEY_CTX_free(mac_ctx);
    return mac_key;
}