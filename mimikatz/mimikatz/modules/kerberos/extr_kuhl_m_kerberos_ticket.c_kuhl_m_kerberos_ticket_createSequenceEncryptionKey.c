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
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BerElement ;

/* Variables and functions */
 int /*<<< orphan*/  ID_CTX_ENCRYPTIONKEY_KEYTYPE ; 
 int /*<<< orphan*/  ID_CTX_ENCRYPTIONKEY_KEYVALUE ; 
 int /*<<< orphan*/  MAKE_CTX_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ber_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kuhl_m_kerberos_ticket_createSequenceEncryptionKey(BerElement * pBer, LONG eType, LPCVOID data, DWORD size)
{
	ber_printf(pBer, "{t{i}t{o}}", MAKE_CTX_TAG(ID_CTX_ENCRYPTIONKEY_KEYTYPE), eType, MAKE_CTX_TAG(ID_CTX_ENCRYPTIONKEY_KEYVALUE), data, size);
}