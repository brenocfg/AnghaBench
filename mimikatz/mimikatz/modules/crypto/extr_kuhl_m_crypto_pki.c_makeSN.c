#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cbData; scalar_t__ pbData; } ;
typedef  TYPE_1__* PCRYPT_INTEGER_BLOB ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ LPCWCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CDGenerateRandomBits (scalar_t__,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 scalar_t__ kull_m_string_stringToHexBuffer (scalar_t__,scalar_t__*,int*) ; 

BOOL makeSN(LPCWCHAR szSn, PCRYPT_INTEGER_BLOB sn)
{
	BOOL status = FALSE;
	if(szSn)
	{
		status = kull_m_string_stringToHexBuffer(szSn, &sn->pbData, &sn->cbData);
		if(!status)
			PRINT_ERROR(L"Unable to use \'%s\' as a HEX string\n", szSn);
	}
	else
	{
		sn->cbData = 20;
		if(sn->pbData = (PBYTE) LocalAlloc(LPTR, sn->cbData))
		{
			status = NT_SUCCESS(CDGenerateRandomBits(sn->pbData, sn->cbData));
			if(!status)
				LocalFree(sn->pbData);
		}
	}
	return status;
}