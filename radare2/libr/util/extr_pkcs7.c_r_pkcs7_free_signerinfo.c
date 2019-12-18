#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  unauthenticatedAttributes; int /*<<< orphan*/  encryptedDigest; int /*<<< orphan*/  digestEncryptionAlgorithm; int /*<<< orphan*/  authenticatedAttributes; int /*<<< orphan*/  digestAlgorithm; int /*<<< orphan*/  issuerAndSerialNumber; } ;
typedef  TYPE_1__ RPKCS7SignerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_asn1_free_binary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_pkcs7_free_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_pkcs7_free_issuerandserialnumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_x509_free_algorithmidentifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_pkcs7_free_signerinfo(RPKCS7SignerInfo *si) {
	if (si) {
		r_pkcs7_free_issuerandserialnumber (&si->issuerAndSerialNumber);
		r_x509_free_algorithmidentifier (&si->digestAlgorithm);
		r_pkcs7_free_attributes (&si->authenticatedAttributes);
		r_x509_free_algorithmidentifier (&si->digestEncryptionAlgorithm);
		r_asn1_free_binary (si->encryptedDigest);
		r_pkcs7_free_attributes (&si->unauthenticatedAttributes);
		free (si);
	}
}