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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_MD_number (int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  EVP_MD_provider (int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  OSSL_PROVIDER_name (int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int md_cmp(const EVP_MD * const *a, const EVP_MD * const *b)
{
    int ret = EVP_MD_number(*a) - EVP_MD_number(*b);

    if (ret == 0)
        ret = strcmp(OSSL_PROVIDER_name(EVP_MD_provider(*a)),
                     OSSL_PROVIDER_name(EVP_MD_provider(*b)));

    return ret;
}