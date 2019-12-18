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
struct TYPE_3__ {scalar_t__ hCard; void* descr; int /*<<< orphan*/  suppdata; void* withoutCard; } ;
typedef  int /*<<< orphan*/  SCARDCONTEXT ;
typedef  TYPE_1__* PKULL_M_ACR_COMM ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  SCARD_PROTOCOL_Tx ; 
 int /*<<< orphan*/  SCARD_PROTOCOL_UNDEFINED ; 
 int /*<<< orphan*/  SCARD_SHARE_DIRECT ; 
 int /*<<< orphan*/  SCARD_SHARE_SHARED ; 
 scalar_t__ SCARD_S_SUCCESS ; 
 scalar_t__ SCardConnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

BOOL kull_m_acr_init(SCARDCONTEXT hContext, LPCWSTR szReaderName, BOOL withoutCard, LPVOID suppdata, BOOL descr, PKULL_M_ACR_COMM comm)
{
	BOOL status = FALSE;
	DWORD dwActiveProtocol;
	LONG scStatus;
	comm->hCard = 0;
	comm->withoutCard = withoutCard;
	comm->suppdata = suppdata;
	comm->descr = descr;
	scStatus = SCardConnect(hContext, szReaderName, withoutCard ? SCARD_SHARE_DIRECT : SCARD_SHARE_SHARED, withoutCard ? SCARD_PROTOCOL_UNDEFINED : SCARD_PROTOCOL_Tx, &comm->hCard, &dwActiveProtocol);
	if(!(status = (scStatus == SCARD_S_SUCCESS)))
		PRINT_ERROR(L"SCardConnect: 0x%08x\n", scStatus);
	return status;
}