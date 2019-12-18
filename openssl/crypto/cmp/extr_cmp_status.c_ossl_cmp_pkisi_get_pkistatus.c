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
struct TYPE_3__ {int /*<<< orphan*/ * status; } ;
typedef  TYPE_1__ OSSL_CMP_PKISI ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_assert (int) ; 
 int ossl_cmp_asn1_get_int (int /*<<< orphan*/ *) ; 

int ossl_cmp_pkisi_get_pkistatus(const OSSL_CMP_PKISI *si)
{
    if (!ossl_assert(si != NULL && si->status != NULL))
        return -1;
    return ossl_cmp_asn1_get_int(si->status);
}