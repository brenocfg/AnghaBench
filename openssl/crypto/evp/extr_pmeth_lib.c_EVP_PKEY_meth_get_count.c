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
 size_t OSSL_NELEM (int /*<<< orphan*/ ) ; 
 scalar_t__ app_pkey_methods ; 
 scalar_t__ sk_EVP_PKEY_METHOD_num (scalar_t__) ; 
 int /*<<< orphan*/  standard_methods ; 

size_t EVP_PKEY_meth_get_count(void)
{
    size_t rv = OSSL_NELEM(standard_methods);

    if (app_pkey_methods)
        rv += sk_EVP_PKEY_METHOD_num(app_pkey_methods);
    return rv;
}