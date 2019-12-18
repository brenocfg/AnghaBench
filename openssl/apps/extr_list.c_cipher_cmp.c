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
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int EVP_CIPHER_number (int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  EVP_CIPHER_provider (int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  OSSL_PROVIDER_name (int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cipher_cmp(const EVP_CIPHER * const *a,
                      const EVP_CIPHER * const *b)
{
    int ret = EVP_CIPHER_number(*a) - EVP_CIPHER_number(*b);

    if (ret == 0)
        ret = strcmp(OSSL_PROVIDER_name(EVP_CIPHER_provider(*a)),
                     OSSL_PROVIDER_name(EVP_CIPHER_provider(*b)));

    return ret;
}