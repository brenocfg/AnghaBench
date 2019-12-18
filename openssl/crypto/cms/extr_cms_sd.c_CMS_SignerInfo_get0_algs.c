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
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {int /*<<< orphan*/ * signatureAlgorithm; int /*<<< orphan*/ * digestAlgorithm; int /*<<< orphan*/ * signer; int /*<<< orphan*/ * pkey; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_1__ CMS_SignerInfo ;

/* Variables and functions */

void CMS_SignerInfo_get0_algs(CMS_SignerInfo *si, EVP_PKEY **pk,
                              X509 **signer, X509_ALGOR **pdig,
                              X509_ALGOR **psig)
{
    if (pk)
        *pk = si->pkey;
    if (signer)
        *signer = si->signer;
    if (pdig)
        *pdig = si->digestAlgorithm;
    if (psig)
        *psig = si->signatureAlgorithm;
}