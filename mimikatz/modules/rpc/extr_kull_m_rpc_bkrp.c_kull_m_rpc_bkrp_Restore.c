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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BACKUPKEY_RESTORE_GUID ; 
 int /*<<< orphan*/  kull_m_rpc_bkrp_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL kull_m_rpc_bkrp_Restore(LPCWSTR NetworkAddr, PVOID DataIn, DWORD dwDataIn, PVOID *pDataOut, DWORD *pdwDataOut)
{
	return kull_m_rpc_bkrp_generic(NetworkAddr, &BACKUPKEY_RESTORE_GUID, DataIn, dwDataIn, pDataOut, pdwDataOut);
}