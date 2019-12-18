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
 int ASN1_BIT_STRING_get_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CMP_R_INVALID_ARGS ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OSSL_CMP_PKIFAILUREINFO_MAX ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

int ossl_cmp_pkisi_pkifailureinfo_check(const OSSL_CMP_PKISI *si, int bit_index)
{
    if (!ossl_assert(si != NULL && si->failInfo != NULL))
        return -1;
    if (bit_index < 0 || bit_index > OSSL_CMP_PKIFAILUREINFO_MAX) {
        CMPerr(0, CMP_R_INVALID_ARGS);
        return -1;
    }

    return ASN1_BIT_STRING_get_bit(si->failInfo, bit_index);
}