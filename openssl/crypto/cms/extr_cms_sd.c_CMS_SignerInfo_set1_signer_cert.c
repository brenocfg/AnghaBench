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
struct TYPE_3__ {int /*<<< orphan*/ * signer; int /*<<< orphan*/  pkey; } ;
typedef  TYPE_1__ CMS_SignerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_pubkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 

void CMS_SignerInfo_set1_signer_cert(CMS_SignerInfo *si, X509 *signer)
{
    if (signer) {
        X509_up_ref(signer);
        EVP_PKEY_free(si->pkey);
        si->pkey = X509_get_pubkey(signer);
    }
    X509_free(si->signer);
    si->signer = signer;
}