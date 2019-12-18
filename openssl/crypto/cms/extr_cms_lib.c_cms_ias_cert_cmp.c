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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {int /*<<< orphan*/  serialNumber; int /*<<< orphan*/  issuer; } ;
typedef  TYPE_1__ CMS_IssuerAndSerialNumber ;

/* Variables and functions */
 int ASN1_INTEGER_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_serialNumber (int /*<<< orphan*/ *) ; 

int cms_ias_cert_cmp(CMS_IssuerAndSerialNumber *ias, X509 *cert)
{
    int ret;
    ret = X509_NAME_cmp(ias->issuer, X509_get_issuer_name(cert));
    if (ret)
        return ret;
    return ASN1_INTEGER_cmp(ias->serialNumber, X509_get_serialNumber(cert));
}