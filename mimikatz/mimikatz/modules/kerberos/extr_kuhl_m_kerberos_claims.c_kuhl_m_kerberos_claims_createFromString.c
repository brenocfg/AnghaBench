#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int ulClaimsCount; TYPE_3__* ClaimEntries; int /*<<< orphan*/  usClaimsSourceType; } ;
struct TYPE_10__ {int ulClaimsArrayCount; TYPE_5__* ClaimsArrays; } ;
struct TYPE_7__ {int ValueCount; void** StringValues; } ;
struct TYPE_8__ {TYPE_1__ cs; } ;
struct TYPE_9__ {TYPE_2__ Values; void* Id; int /*<<< orphan*/  Type; } ;
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  TYPE_3__* PCLAIM_ENTRY ;
typedef  TYPE_4__* PCLAIMS_SET ;
typedef  TYPE_5__* PCLAIMS_ARRAY ;
typedef  void* LPWSTR ;
typedef  int /*<<< orphan*/ * LPCWCHAR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  CLAIM_ENTRY ;
typedef  int /*<<< orphan*/  CLAIMS_SET ;
typedef  int /*<<< orphan*/  CLAIMS_ARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  CLAIMS_SOURCE_TYPE_AD ; 
 int /*<<< orphan*/  CLAIM_TYPE_STRING ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 void* _wcsdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wcstok_s (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 

PCLAIMS_SET kuhl_m_kerberos_claims_createFromString(LPCWCHAR string)
{
	PCLAIMS_SET set = NULL;
	PWCHAR dupClaims, dupSet, dupEnt, nextSetToken, SetToken, nextArrayToken, ArrayToken, nextKeyToken, KeyToken, nextValueToken, ValueToken;
	DWORD curArr, curEnt, curVal;

	if(set = (PCLAIMS_SET) LocalAlloc(LPTR, sizeof(CLAIMS_SET)))
	{
		if(dupClaims = _wcsdup(string))
		{
			for(nextSetToken = NULL, SetToken = wcstok_s(dupClaims, L";", &nextSetToken); SetToken; SetToken = wcstok_s(NULL, L";", &nextSetToken))
				set->ulClaimsArrayCount++;
			free(dupClaims);
		}
		if(set->ClaimsArrays = (PCLAIMS_ARRAY) LocalAlloc(LPTR, sizeof(CLAIMS_ARRAY) * set->ulClaimsArrayCount)) //
		{
			if(dupClaims = _wcsdup(string))
			{
				for(nextSetToken = NULL, curArr = 0, SetToken = wcstok_s(dupClaims, L";", &nextSetToken); SetToken; curArr++, SetToken = wcstok_s(NULL, L";", &nextSetToken))
				{
					set->ClaimsArrays[curArr].usClaimsSourceType = CLAIMS_SOURCE_TYPE_AD;
					if(dupSet = _wcsdup(SetToken))
					{
						for(nextArrayToken = NULL, ArrayToken = wcstok_s(dupSet, L",", &nextArrayToken); ArrayToken; ArrayToken = wcstok_s(NULL, L",", &nextArrayToken))
							set->ClaimsArrays[curArr].ulClaimsCount++;
						free(dupSet);
					}
					if(set->ClaimsArrays[curArr].ClaimEntries = (PCLAIM_ENTRY) LocalAlloc(LPTR, sizeof(CLAIM_ENTRY) * set->ClaimsArrays[curArr].ulClaimsCount)) //
					{
						for(nextArrayToken = NULL, curEnt = 0, ArrayToken = wcstok_s(SetToken, L",", &nextArrayToken); ArrayToken; curEnt++, ArrayToken = wcstok_s(NULL, L",", &nextArrayToken))
						{
							set->ClaimsArrays[curArr].ClaimEntries[curEnt].Type = CLAIM_TYPE_STRING;
							nextKeyToken = NULL;
							if(KeyToken = wcstok_s(ArrayToken, L"=", &nextKeyToken))
							{
								if(set->ClaimsArrays[curArr].ClaimEntries[curEnt].Id = _wcsdup(KeyToken)) //
								{
									if(KeyToken = wcstok_s(NULL, L"=", &nextKeyToken))
									{
										if(dupEnt = _wcsdup(KeyToken))
										{
											for(nextValueToken = NULL, ValueToken = wcstok_s(dupEnt, L"|", &nextValueToken); ValueToken; ValueToken = wcstok_s(NULL, L"|", &nextValueToken))
												set->ClaimsArrays[curArr].ClaimEntries[curEnt].Values.cs.ValueCount++;
											free(dupEnt);
										}
										if(set->ClaimsArrays[curArr].ClaimEntries[curEnt].Values.cs.StringValues = (LPWSTR *) LocalAlloc(LPTR, sizeof(LPWSTR) * set->ClaimsArrays[curArr].ClaimEntries[curEnt].Values.cs.ValueCount)) //
											for(nextValueToken = NULL, curVal = 0, ValueToken = wcstok_s(KeyToken, L"|", &nextValueToken); ValueToken; curVal++, ValueToken = wcstok_s(NULL, L"|", &nextValueToken))
												set->ClaimsArrays[curArr].ClaimEntries[curEnt].Values.cs.StringValues[curVal] = _wcsdup(ValueToken); //
									}
								}
							}
						}
					}
				}
				free(dupClaims);
			}
		}
	}
	return set;
}