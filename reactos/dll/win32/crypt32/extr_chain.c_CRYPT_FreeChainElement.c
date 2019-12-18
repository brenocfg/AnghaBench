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
struct TYPE_4__ {int /*<<< orphan*/  pCertContext; } ;
typedef  TYPE_1__* PCERT_CHAIN_ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  CertFreeCertificateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_1__*) ; 

__attribute__((used)) static void CRYPT_FreeChainElement(PCERT_CHAIN_ELEMENT element)
{
    CertFreeCertificateContext(element->pCertContext);
    CryptMemFree(element);
}