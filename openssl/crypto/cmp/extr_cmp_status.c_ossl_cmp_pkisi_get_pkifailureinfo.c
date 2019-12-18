#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * failInfo; } ;
typedef  TYPE_1__ OSSL_CMP_PKISI ;

/* Variables and functions */
 scalar_t__ ASN1_BIT_STRING_get_bit (int /*<<< orphan*/ *,int) ; 
 int OSSL_CMP_PKIFAILUREINFO_MAX ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

int ossl_cmp_pkisi_get_pkifailureinfo(const OSSL_CMP_PKISI *si)
{
    int i;
    int res = 0;

    if (!ossl_assert(si != NULL && si->failInfo != NULL))
        return -1;
    for (i = 0; i <= OSSL_CMP_PKIFAILUREINFO_MAX; i++)
        if (ASN1_BIT_STRING_get_bit(si->failInfo, i))
            res |= 1 << i;
    return res;
}