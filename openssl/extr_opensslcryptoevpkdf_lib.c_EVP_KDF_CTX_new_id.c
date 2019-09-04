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
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_KDF_CTX_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_get_kdfbynid (int) ; 

EVP_KDF_CTX *EVP_KDF_CTX_new_id(int id)
{
    const EVP_KDF *kdf = EVP_get_kdfbynid(id);

    if (kdf == NULL)
        return NULL;
    return EVP_KDF_CTX_new(kdf);
}