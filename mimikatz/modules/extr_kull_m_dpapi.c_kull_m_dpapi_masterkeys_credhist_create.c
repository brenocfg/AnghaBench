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
typedef  int /*<<< orphan*/ * PKULL_M_DPAPI_MASTERKEY_CREDHIST ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int /*<<< orphan*/  KULL_M_DPAPI_MASTERKEY_CREDHIST ;
typedef  int /*<<< orphan*/  DWORD64 ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

PKULL_M_DPAPI_MASTERKEY_CREDHIST kull_m_dpapi_masterkeys_credhist_create(LPCVOID data, DWORD64 size)
{
	PKULL_M_DPAPI_MASTERKEY_CREDHIST credhist = NULL;
	if(data && (credhist = (PKULL_M_DPAPI_MASTERKEY_CREDHIST) LocalAlloc(LPTR, sizeof(KULL_M_DPAPI_MASTERKEY_CREDHIST))))
		RtlCopyMemory(credhist, data, sizeof(KULL_M_DPAPI_MASTERKEY_CREDHIST));
	return credhist;
}