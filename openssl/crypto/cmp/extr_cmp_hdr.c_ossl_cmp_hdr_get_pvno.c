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
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  pvno; } ;
typedef  TYPE_1__ OSSL_CMP_PKIHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_get_int64 (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 

int ossl_cmp_hdr_get_pvno(const OSSL_CMP_PKIHEADER *hdr)
{
    int64_t pvno;

    if (!ossl_assert(hdr != NULL))
        return -1;
    if (!ASN1_INTEGER_get_int64(&pvno, hdr->pvno) || pvno < 0 || pvno > INT_MAX)
        return -1;
    return (int)pvno;
}