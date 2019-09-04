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
typedef  int /*<<< orphan*/  EVP_PKEY_METHOD ;

/* Variables and functions */
 size_t OSSL_NELEM (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * app_pkey_methods ; 
 scalar_t__ sk_EVP_PKEY_METHOD_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* sk_EVP_PKEY_METHOD_value (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  const** standard_methods ; 

const EVP_PKEY_METHOD *EVP_PKEY_meth_get0(size_t idx)
{
    if (idx < OSSL_NELEM(standard_methods))
        return standard_methods[idx];
    if (app_pkey_methods == NULL)
        return NULL;
    idx -= OSSL_NELEM(standard_methods);
    if (idx >= (size_t)sk_EVP_PKEY_METHOD_num(app_pkey_methods))
        return NULL;
    return sk_EVP_PKEY_METHOD_value(app_pkey_methods, idx);
}