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
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_3__ {int /*<<< orphan*/  sender; } ;
typedef  TYPE_1__ OSSL_CMP_PKIHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 
 int set1_general_name (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int ossl_cmp_hdr_set1_sender(OSSL_CMP_PKIHEADER *hdr, const X509_NAME *nm)
{
    if (!ossl_assert(hdr != NULL))
        return 0;
    return set1_general_name(&hdr->sender, nm);
}