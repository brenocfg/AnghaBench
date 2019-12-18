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
struct TYPE_3__ {int /*<<< orphan*/  pvno; } ;
typedef  TYPE_1__ OSSL_CMP_PKIHEADER ;

/* Variables and functions */
 int ASN1_INTEGER_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 

int ossl_cmp_hdr_set_pvno(OSSL_CMP_PKIHEADER *hdr, int pvno)
{
    if (!ossl_assert(hdr != NULL))
        return 0;
    return ASN1_INTEGER_set(hdr->pvno, pvno);
}