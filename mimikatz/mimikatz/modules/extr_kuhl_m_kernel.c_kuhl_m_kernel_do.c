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
struct TYPE_3__ {int /*<<< orphan*/  ioctlCode; int /*<<< orphan*/  (* pCommand ) (int,int /*<<< orphan*/ **) ;int /*<<< orphan*/  command; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 unsigned short ARRAYSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/ ** CommandLineToArgvW (int /*<<< orphan*/ *,int*) ; 
 int FALSE ; 
 int /*<<< orphan*/  IOCTL_MIMIDRV_RAW ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* kuhl_k_c_kernel ; 
 int /*<<< orphan*/  kull_m_kernel_mimidrv_simple_output (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ **) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_kernel_do(wchar_t * input)
{
	NTSTATUS status = STATUS_SUCCESS;
	int argc;
	wchar_t ** argv = CommandLineToArgvW(input, &argc);
	unsigned short indexCommand;
	BOOL commandFound = FALSE;

	if(argv && (argc > 0))
	{
		for(indexCommand = 0; !commandFound && (indexCommand < ARRAYSIZE(kuhl_k_c_kernel)); indexCommand++)
		{
			if(commandFound = _wcsicmp(argv[0], kuhl_k_c_kernel[indexCommand].command) == 0)
			{
				if(kuhl_k_c_kernel[indexCommand].pCommand)
					status = kuhl_k_c_kernel[indexCommand].pCommand(argc - 1, argv + 1);
				else
					kull_m_kernel_mimidrv_simple_output(kuhl_k_c_kernel[indexCommand].ioctlCode, NULL, 0);
			}
		}
		if(!commandFound)
			kull_m_kernel_mimidrv_simple_output(IOCTL_MIMIDRV_RAW, input, (DWORD) (wcslen(input) + 1) * sizeof(wchar_t));
	}
	return status;
}