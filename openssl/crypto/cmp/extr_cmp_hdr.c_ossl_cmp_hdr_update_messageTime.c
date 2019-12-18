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
struct TYPE_3__ {int /*<<< orphan*/ * messageTime; } ;
typedef  TYPE_1__ OSSL_CMP_PKIHEADER ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_GENERALIZEDTIME_new () ; 
 int /*<<< orphan*/ * ASN1_GENERALIZEDTIME_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int ossl_cmp_hdr_update_messageTime(OSSL_CMP_PKIHEADER *hdr)
{
    if (!ossl_assert(hdr != NULL))
        return 0;
    if (hdr->messageTime == NULL
            && (hdr->messageTime = ASN1_GENERALIZEDTIME_new()) == NULL)
        return 0;
    return ASN1_GENERALIZEDTIME_set(hdr->messageTime, time(NULL)) != NULL;
}