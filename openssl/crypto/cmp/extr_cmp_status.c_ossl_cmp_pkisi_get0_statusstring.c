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
struct TYPE_3__ {int /*<<< orphan*/ * statusString; } ;
typedef  TYPE_1__ OSSL_CMP_PKISI ;
typedef  int /*<<< orphan*/  OSSL_CMP_PKIFREETEXT ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 

OSSL_CMP_PKIFREETEXT *ossl_cmp_pkisi_get0_statusstring(const OSSL_CMP_PKISI *si)
{
    if (!ossl_assert(si != NULL))
        return NULL;
    return si->statusString;
}