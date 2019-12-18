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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int* RPC_WSTR ;
typedef  scalar_t__ RPC_STATUS ;
typedef  int* PBYTE ;
typedef  int* LPWSTR ;
typedef  int* LPCWSTR ;
typedef  int /*<<< orphan*/  LPCGUID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  RpcStringFree (int**) ; 
 int /*<<< orphan*/  RtlCopyMemory (int*,int*,int) ; 
 scalar_t__ UuidToString (int /*<<< orphan*/ ,int**) ; 
 int lstrlen (int*) ; 

LPWSTR kull_m_rpc_drsr_MakeSpnWithGUID(LPCGUID ServClass, LPCWSTR ServName, LPCGUID InstName)
{
	LPWSTR result = NULL;
	RPC_STATUS status;
	RPC_WSTR szServClass, szInstName;
	DWORD dwServClass, dwInstName, dwServName;
	status = UuidToString(ServClass, &szServClass);
	if(status == RPC_S_OK)
	{
		status = UuidToString(InstName, &szInstName);
		if(status == RPC_S_OK)
		{
			dwServClass = lstrlen((LPWSTR) szServClass) * sizeof(wchar_t);
			dwInstName = lstrlen((LPWSTR) szInstName) * sizeof(wchar_t);
			dwServName = lstrlen(ServName) * sizeof(wchar_t);
			if (result = (LPWSTR) LocalAlloc(LPTR, dwServClass + sizeof(wchar_t) + dwInstName + sizeof(wchar_t) + dwServName))
			{
				RtlCopyMemory(result, szServClass, dwServClass);
				RtlCopyMemory((PBYTE) result + dwServClass + sizeof(wchar_t), szInstName, dwInstName);
				((PBYTE) result)[dwServClass] = L'/';
				RtlCopyMemory((PBYTE) result + dwServClass + sizeof(wchar_t) + dwServName + sizeof(wchar_t), ServName, dwServName);
				((PBYTE) result)[dwServClass + sizeof(wchar_t) + dwServName] = L'/';
			}
			RpcStringFree(&szInstName);
		}
		else PRINT_ERROR(L"UuidToString(i): %08x\n", status);
		RpcStringFree(&szServClass);
	}
	else PRINT_ERROR(L"UuidToString(s): %08x\n", status);
	return result;
}