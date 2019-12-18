#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t cChain; TYPE_2__* rgpChain; } ;
struct TYPE_8__ {int /*<<< orphan*/  world; TYPE_1__ context; } ;
typedef  size_t DWORD ;
typedef  TYPE_2__ CertificateChain ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_FreeLowerQualityChains (TYPE_2__*) ; 
 int /*<<< orphan*/  CRYPT_FreeSimpleChain (TYPE_2__) ; 
 int /*<<< orphan*/  CertCloseStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (TYPE_2__*) ; 

__attribute__((used)) static void CRYPT_FreeChainContext(CertificateChain *chain)
{
    DWORD i;

    CRYPT_FreeLowerQualityChains(chain);
    for (i = 0; i < chain->context.cChain; i++)
        CRYPT_FreeSimpleChain(chain->context.rgpChain[i]);
    CryptMemFree(chain->context.rgpChain);
    CertCloseStore(chain->world, 0);
    CryptMemFree(chain);
}