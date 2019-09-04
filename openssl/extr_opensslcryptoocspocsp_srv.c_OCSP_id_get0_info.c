#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * algorithm; } ;
struct TYPE_5__ {int /*<<< orphan*/  serialNumber; int /*<<< orphan*/  issuerKeyHash; int /*<<< orphan*/  issuerNameHash; TYPE_1__ hashAlgorithm; } ;
typedef  TYPE_2__ OCSP_CERTID ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */

int OCSP_id_get0_info(ASN1_OCTET_STRING **piNameHash, ASN1_OBJECT **pmd,
                      ASN1_OCTET_STRING **pikeyHash,
                      ASN1_INTEGER **pserial, OCSP_CERTID *cid)
{
    if (!cid)
        return 0;
    if (pmd)
        *pmd = cid->hashAlgorithm.algorithm;
    if (piNameHash)
        *piNameHash = &cid->issuerNameHash;
    if (pikeyHash)
        *pikeyHash = &cid->issuerKeyHash;
    if (pserial)
        *pserial = &cid->serialNumber;
    return 1;
}