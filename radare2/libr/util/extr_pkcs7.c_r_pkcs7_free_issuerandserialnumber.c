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
struct TYPE_3__ {int /*<<< orphan*/  serialNumber; int /*<<< orphan*/  issuer; } ;
typedef  TYPE_1__ RPKCS7IssuerAndSerialNumber ;

/* Variables and functions */
 int /*<<< orphan*/  r_asn1_free_binary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_x509_free_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_pkcs7_free_issuerandserialnumber(RPKCS7IssuerAndSerialNumber *iasu) {
	if (iasu) {
		r_x509_free_name (&iasu->issuer);
		r_asn1_free_binary (iasu->serialNumber);
		// Used internally pkcs #7, so it shouldn't free iasu.
	}
}