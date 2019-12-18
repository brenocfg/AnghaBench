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
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_3__ {int /*<<< orphan*/  isFound; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ KKLL_M_MODULE_FROM_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kkll_m_modules_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kkll_m_modules_fromAddr_callback ; 
 int /*<<< orphan*/  kprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

NTSTATUS kkll_m_modules_fromAddr(PKIWI_BUFFER outBuffer, PVOID addr)
{
	KKLL_M_MODULE_FROM_ADDR structAddr = {FALSE, (ULONG_PTR) addr};
	NTSTATUS status = kkll_m_modules_enum(0, NULL, outBuffer, kkll_m_modules_fromAddr_callback, &structAddr);

	if(NT_SUCCESS(status) && !structAddr.isFound)
		status = kprintf(outBuffer, L"0x%p [ ? ]\n", addr);

	return status;
}