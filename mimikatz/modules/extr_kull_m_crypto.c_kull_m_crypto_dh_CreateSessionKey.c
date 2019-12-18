#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sessionType; } ;
struct TYPE_8__ {TYPE_1__ publicKey; scalar_t__ hSessionKey; int /*<<< orphan*/  hPrivateKey; int /*<<< orphan*/  hProvParty; } ;
struct TYPE_7__ {scalar_t__ sessionType; int /*<<< orphan*/  cbPublicKey; int /*<<< orphan*/  pbPublicKey; } ;
typedef  TYPE_2__* PMIMI_PUBLICKEY ;
typedef  TYPE_3__* PKIWI_DH ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CryptDestroyKey (scalar_t__) ; 
 scalar_t__ CryptImportKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  CryptSetKeyParam (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KP_ALGID ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  kull_m_crypto_algid_to_name (scalar_t__) ; 

BOOL kull_m_crypto_dh_CreateSessionKey(PKIWI_DH dh, PMIMI_PUBLICKEY publicKey)
{
	BOOL status = FALSE;
	dh->hSessionKey = 0;
	if(dh && publicKey)
	{
		if(dh->publicKey.sessionType == publicKey->sessionType)
		{
			if(CryptImportKey(dh->hProvParty, publicKey->pbPublicKey, publicKey->cbPublicKey, dh->hPrivateKey, 0, &dh->hSessionKey))
			{
				if(!(status = CryptSetKeyParam(dh->hSessionKey, KP_ALGID, (PBYTE) &dh->publicKey.sessionType, 0)))
				{
					PRINT_ERROR_AUTO(L"CryptSetKeyParam");
					CryptDestroyKey(dh->hSessionKey);
					dh->hSessionKey = 0;
				}
			}
			else PRINT_ERROR_AUTO(L"CryptImportKey");

		}
		else PRINT_ERROR(L"Alg mismatch: DH - %s (%08x) / P - %s (%08x)\n", kull_m_crypto_algid_to_name(dh->publicKey.sessionType), dh->publicKey.sessionType, kull_m_crypto_algid_to_name(publicKey->sessionType), publicKey->sessionType);
	}
	return status;
}