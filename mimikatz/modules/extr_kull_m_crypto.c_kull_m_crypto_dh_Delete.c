#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* pbPublicKey; } ;
struct TYPE_7__ {scalar_t__ hProvParty; scalar_t__ hSessionKey; scalar_t__ hPrivateKey; TYPE_1__ publicKey; } ;
typedef  TYPE_2__* PKIWI_DH ;

/* Variables and functions */
 int /*<<< orphan*/  CryptDestroyKey (scalar_t__) ; 
 int /*<<< orphan*/  CryptReleaseContext (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ LocalFree (TYPE_2__*) ; 

PKIWI_DH kull_m_crypto_dh_Delete(PKIWI_DH dh)
{
	if(dh)
	{
		if(dh->publicKey.pbPublicKey)
			LocalFree(dh->publicKey.pbPublicKey);
		if(dh->hPrivateKey)
			CryptDestroyKey(dh->hPrivateKey);
		if(dh->hSessionKey)
			CryptDestroyKey(dh->hSessionKey);
		if(dh->hProvParty)
			CryptReleaseContext(dh->hProvParty, 0);
		dh = (PKIWI_DH) LocalFree(dh);
	}
	return dh;
}