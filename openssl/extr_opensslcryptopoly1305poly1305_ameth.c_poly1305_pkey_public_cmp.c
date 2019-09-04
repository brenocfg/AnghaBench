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

/* Variables and functions */
 int ASN1_OCTET_STRING_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_get0 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int poly1305_pkey_public_cmp(const EVP_PKEY *a, const EVP_PKEY *b)
{
    return ASN1_OCTET_STRING_cmp(EVP_PKEY_get0(a), EVP_PKEY_get0(b));
}