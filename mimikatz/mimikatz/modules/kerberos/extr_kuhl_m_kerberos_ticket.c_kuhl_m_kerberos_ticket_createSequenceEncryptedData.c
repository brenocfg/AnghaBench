#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BerElement ;

/* Variables and functions */
 int /*<<< orphan*/  ID_CTX_ENCRYPTEDDATA_CIPHER ; 
 int /*<<< orphan*/  ID_CTX_ENCRYPTEDDATA_ETYPE ; 
 int /*<<< orphan*/  ID_CTX_ENCRYPTEDDATA_KVNO ; 
 int /*<<< orphan*/  MAKE_CTX_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ber_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

void kuhl_m_kerberos_ticket_createSequenceEncryptedData(BerElement * pBer, LONG eType, ULONG kvNo, LPCVOID data, DWORD size)
{
	ber_printf(pBer, "{t{i}", MAKE_CTX_TAG(ID_CTX_ENCRYPTEDDATA_ETYPE), eType);
	if(eType)
		ber_printf(pBer, "t{i}", MAKE_CTX_TAG(ID_CTX_ENCRYPTEDDATA_KVNO), kvNo);
	ber_printf(pBer, "t{o}}", MAKE_CTX_TAG(ID_CTX_ENCRYPTEDDATA_CIPHER), data, size);
}