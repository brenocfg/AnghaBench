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
typedef  int /*<<< orphan*/  EVP_PKEY_ASN1_METHOD ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_asn1_find_str (int /*<<< orphan*/ **,char const*,int) ; 
 scalar_t__ EVP_PKEY_asn1_get0_info (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int get_optional_pkey_id(const char *pkey_name)
{
    const EVP_PKEY_ASN1_METHOD *ameth;
    ENGINE *tmpeng = NULL;
    int pkey_id = 0;
    ameth = EVP_PKEY_asn1_find_str(&tmpeng, pkey_name, -1);
    if (ameth) {
        if (EVP_PKEY_asn1_get0_info(&pkey_id, NULL, NULL, NULL, NULL,
                                    ameth) <= 0)
            pkey_id = 0;
    }
    ENGINE_finish(tmpeng);
    return pkey_id;
}