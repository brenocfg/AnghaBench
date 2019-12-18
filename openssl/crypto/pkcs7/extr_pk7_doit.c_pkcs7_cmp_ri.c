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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_5__ {TYPE_1__* issuer_and_serial; } ;
struct TYPE_4__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  issuer; } ;
typedef  TYPE_2__ PKCS7_RECIP_INFO ;

/* Variables and functions */
 int ASN1_INTEGER_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_NAME_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_serialNumber (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkcs7_cmp_ri(PKCS7_RECIP_INFO *ri, X509 *pcert)
{
    int ret;
    ret = X509_NAME_cmp(ri->issuer_and_serial->issuer,
                        X509_get_issuer_name(pcert));
    if (ret)
        return ret;
    return ASN1_INTEGER_cmp(X509_get_serialNumber(pcert),
                            ri->issuer_and_serial->serial);
}