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
struct TYPE_4__ {int /*<<< orphan*/  algorithm; } ;
struct TYPE_5__ {int /*<<< orphan*/  serialNumber; int /*<<< orphan*/  issuerKeyHash; int /*<<< orphan*/  issuerNameHash; TYPE_1__ hashAlgorithm; } ;
typedef  TYPE_2__ OCSP_CERTID ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  i2a_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2a_ASN1_OBJECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2a_ASN1_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocsp_certid_print(BIO *bp, OCSP_CERTID *a, int indent)
{
    BIO_printf(bp, "%*sCertificate ID:\n", indent, "");
    indent += 2;
    BIO_printf(bp, "%*sHash Algorithm: ", indent, "");
    i2a_ASN1_OBJECT(bp, a->hashAlgorithm.algorithm);
    BIO_printf(bp, "\n%*sIssuer Name Hash: ", indent, "");
    i2a_ASN1_STRING(bp, &a->issuerNameHash, 0);
    BIO_printf(bp, "\n%*sIssuer Key Hash: ", indent, "");
    i2a_ASN1_STRING(bp, &a->issuerKeyHash, 0);
    BIO_printf(bp, "\n%*sSerial Number: ", indent, "");
    i2a_ASN1_INTEGER(bp, &a->serialNumber);
    BIO_printf(bp, "\n");
    return 1;
}