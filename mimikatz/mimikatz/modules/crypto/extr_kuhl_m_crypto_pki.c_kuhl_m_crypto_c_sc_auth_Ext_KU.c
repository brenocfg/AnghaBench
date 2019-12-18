#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bits ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_6__ {int member_0; int member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_5__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  pszObjId; int /*<<< orphan*/  fCritical; } ;
typedef  TYPE_1__* PCERT_EXTENSION ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  TYPE_2__ CRYPT_BIT_BLOB ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  kuhl_m_crypto_c_sc_auth_quickEncode (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szOID_KEY_USAGE ; 

BOOL kuhl_m_crypto_c_sc_auth_Ext_KU(PCERT_EXTENSION pCertExtension, BOOL isCritical, WORD bits)
{
	CRYPT_BIT_BLOB bit = {sizeof(bits), (PBYTE) &bits, 5};
	pCertExtension->pszObjId = szOID_KEY_USAGE;
	pCertExtension->fCritical = isCritical;
	return kuhl_m_crypto_c_sc_auth_quickEncode(pCertExtension->pszObjId, &bit, &pCertExtension->Value);
}