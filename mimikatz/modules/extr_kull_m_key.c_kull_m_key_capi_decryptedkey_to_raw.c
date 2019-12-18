#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char magic; int bitlen; char pubexp; } ;
struct TYPE_5__ {int /*<<< orphan*/  aiKeyAlg; scalar_t__ reserved; int /*<<< orphan*/  bVersion; int /*<<< orphan*/  bType; } ;
struct TYPE_7__ {TYPE_2__ RsaKey; TYPE_1__ Header; } ;
typedef  int /*<<< orphan*/  RSA_GENERICKEY_BLOB ;
typedef  TYPE_3__* PRSA_GENERICKEY_BLOB ;
typedef  char* PDWORD ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ LPCVOID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_RSA_KEYX ; 
 int /*<<< orphan*/  CUR_BLOB_VERSION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PRIVATEKEYBLOB ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL kull_m_key_capi_decryptedkey_to_raw(LPCVOID decrypted, DWORD decryptedLen, PRSA_GENERICKEY_BLOB *blob, DWORD *blobLen)
{
	BOOL status = FALSE;
	DWORD keyLen;
	PBYTE ptrDestination, ptrSource;

	if(((PDWORD) decrypted)[0] == '2ASR')
	{
		keyLen = ((PDWORD) decrypted)[2];
		*blobLen = sizeof(RSA_GENERICKEY_BLOB) + ((keyLen * 9) / 16);
		if(*blob = (PRSA_GENERICKEY_BLOB) LocalAlloc(LPTR, *blobLen))
		{
			status = TRUE;
			(*blob)->Header.bType = PRIVATEKEYBLOB;
			(*blob)->Header.bVersion = CUR_BLOB_VERSION;
			(*blob)->Header.reserved = 0;
			(*blob)->Header.aiKeyAlg = CALG_RSA_KEYX;

			(*blob)->RsaKey.magic = ((PDWORD) decrypted)[0];
			(*blob)->RsaKey.bitlen = keyLen;
			(*blob)->RsaKey.pubexp = ((PDWORD) decrypted)[4];

			ptrDestination = ((PBYTE) (*blob)) + sizeof(RSA_GENERICKEY_BLOB);
			ptrSource = (PBYTE) ((PDWORD) decrypted + 5);

			RtlCopyMemory(ptrDestination, ptrSource, keyLen / 8);
			ptrDestination += keyLen / 8;
			ptrSource += (keyLen / 8) + 8;
			RtlCopyMemory(ptrDestination, ptrSource, keyLen / 16);
			ptrDestination += keyLen / 16;
			ptrSource += (keyLen / 16) + 4;
			RtlCopyMemory(ptrDestination, ptrSource, keyLen / 16);
			ptrDestination += keyLen / 16;
			ptrSource += (keyLen / 16) + 4;
			RtlCopyMemory(ptrDestination, ptrSource, keyLen / 16);
			ptrDestination += keyLen / 16;
			ptrSource += (keyLen / 16) + 4;
			RtlCopyMemory(ptrDestination, ptrSource, keyLen / 16);
			ptrDestination += keyLen / 16;
			ptrSource += (keyLen / 16) + 4;
			RtlCopyMemory(ptrDestination, ptrSource, keyLen / 16);
			ptrDestination += keyLen / 16;
			ptrSource += (keyLen / 16) + 4;
			RtlCopyMemory(ptrDestination, ptrSource, keyLen / 8);
		}
	}
	return status;
}