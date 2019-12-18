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
struct TYPE_7__ {int /*<<< orphan*/  fCA; } ;
struct TYPE_6__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  pszObjId; int /*<<< orphan*/  fCritical; } ;
typedef  TYPE_1__* PCERT_EXTENSION ;
typedef  TYPE_2__* PCERT_BASIC_CONSTRAINTS2_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  kuhl_m_crypto_c_sc_auth_quickEncode (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szOID_BASIC_CONSTRAINTS2 ; 

BOOL givebc2(PCERT_EXTENSION pCertExtension, PCERT_BASIC_CONSTRAINTS2_INFO info)
{
	pCertExtension->pszObjId = szOID_BASIC_CONSTRAINTS2;
	pCertExtension->fCritical = info->fCA; // :)
	return kuhl_m_crypto_c_sc_auth_quickEncode(pCertExtension->pszObjId, info, &pCertExtension->Value);
}