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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DRS_MSG_ADDENTRYREQ ;
typedef  int /*<<< orphan*/  DRS_MSG_ADDENTRYREPLY ;
typedef  int /*<<< orphan*/  DRS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_NOT_IMPLEMENTED ; 

ULONG SRV_IDL_DRSAddEntryNotImplemented(DRS_HANDLE hDrs, DWORD dwInVersion, DRS_MSG_ADDENTRYREQ *pmsgIn, DWORD *pdwOutVersion, DRS_MSG_ADDENTRYREPLY *pmsgOut)
{
	return STATUS_NOT_IMPLEMENTED;
}