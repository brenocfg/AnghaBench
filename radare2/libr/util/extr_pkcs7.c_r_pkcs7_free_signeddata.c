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
struct TYPE_3__ {int /*<<< orphan*/  signerinfos; int /*<<< orphan*/  crls; int /*<<< orphan*/  certificates; int /*<<< orphan*/  contentInfo; int /*<<< orphan*/  digestAlgorithms; } ;
typedef  TYPE_1__ RPKCS7SignedData ;

/* Variables and functions */
 int /*<<< orphan*/  r_pkcs7_free_certificaterevocationlists (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_pkcs7_free_contentinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_pkcs7_free_digestalgorithmidentifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_pkcs7_free_extendedcertificatesandcertificates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_pkcs7_free_signerinfos (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r_pkcs7_free_signeddata(RPKCS7SignedData *sd) {
	if (sd) {
		r_pkcs7_free_digestalgorithmidentifier (&sd->digestAlgorithms);
		r_pkcs7_free_contentinfo (&sd->contentInfo);
		r_pkcs7_free_extendedcertificatesandcertificates (&sd->certificates);
		r_pkcs7_free_certificaterevocationlists (&sd->crls);
		r_pkcs7_free_signerinfos (&sd->signerinfos);
		// Used internally pkcs #7, so it shouldn't free sd.
	}
}