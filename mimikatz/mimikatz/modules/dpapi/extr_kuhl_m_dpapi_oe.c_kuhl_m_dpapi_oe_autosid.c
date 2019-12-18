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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertSidToStringSid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ConvertStringSidToSid (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int* _wcsdup (scalar_t__) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int* wcsrchr (int*,int) ; 

BOOL kuhl_m_dpapi_oe_autosid(LPCWSTR filename, LPWSTR * pSid)
{
	BOOL status = FALSE;
	wchar_t *duplicate, *pE;
	PSID tmpSid;
	if(filename && (duplicate = _wcsdup(filename)))
	{
		if(pE = wcsrchr(duplicate, L'\\'))
		{
			*pE = L'\0';
			if(pE = wcsrchr(duplicate, L'\\'))
			{
				if(ConvertStringSidToSid(++pE, &tmpSid))
				{
					if(status = ConvertSidToStringSid(tmpSid, pSid))
					{
						kprintf(L"Auto SID from path seems to be: %s\n", *pSid);
					}
					LocalFree(tmpSid);
				}
			}
		}
		free(duplicate);
	}
	return status;
}