#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_13__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  pszObjId; int /*<<< orphan*/  fCritical; } ;
struct TYPE_10__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_12__ {TYPE_1__ PublicKey; } ;
struct TYPE_11__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_2__ SHA_DIGEST ;
typedef  int /*<<< orphan*/  SHA_CTX ;
typedef  TYPE_3__* PCERT_PUBLIC_KEY_INFO ;
typedef  TYPE_4__* PCERT_EXTENSION ;
typedef  TYPE_5__ CRYPT_DATA_BLOB ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  A_SHAFinal (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  A_SHAInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  A_SHAUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  kuhl_m_crypto_c_sc_auth_quickEncode (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szOID_SUBJECT_KEY_IDENTIFIER ; 

BOOL giveski(PCERT_EXTENSION pCertExtension, PCERT_PUBLIC_KEY_INFO info)
{
	SHA_CTX ctx;
	SHA_DIGEST dgst;
	CRYPT_DATA_BLOB bit = {sizeof(dgst.digest), dgst.digest};
	A_SHAInit(&ctx);
	A_SHAUpdate(&ctx, info->PublicKey.pbData, info->PublicKey.cbData);
	A_SHAFinal(&ctx, &dgst);
	pCertExtension->pszObjId = szOID_SUBJECT_KEY_IDENTIFIER;
	pCertExtension->fCritical = FALSE;
	return kuhl_m_crypto_c_sc_auth_quickEncode(pCertExtension->pszObjId, &bit, &pCertExtension->Value);
}