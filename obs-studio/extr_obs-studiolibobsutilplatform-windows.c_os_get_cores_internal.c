#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_5__ {scalar_t__ Relationship; int /*<<< orphan*/  ProcessorMask; } ;
typedef  TYPE_1__* PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetLogicalProcessorInformation (TYPE_1__*,int*) ; 
 scalar_t__ RelationProcessorCore ; 
 int core_count_initialized ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  logical_cores ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ num_logical_cores (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physical_cores ; 

__attribute__((used)) static void os_get_cores_internal(void)
{
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION info = NULL, temp = NULL;
	DWORD len = 0;

	if (core_count_initialized)
		return;

	core_count_initialized = true;

	GetLogicalProcessorInformation(info, &len);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		return;

	info = malloc(len);

	if (GetLogicalProcessorInformation(info, &len)) {
		DWORD num = len / sizeof(*info);
		temp = info;

		for (DWORD i = 0; i < num; i++) {
			if (temp->Relationship == RelationProcessorCore) {
				ULONG_PTR mask = temp->ProcessorMask;

				physical_cores++;
				logical_cores += num_logical_cores(mask);
			}

			temp++;
		}
	}

	free(info);
}