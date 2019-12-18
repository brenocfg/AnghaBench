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
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PRTL_DEBUG_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 scalar_t__ NtAllocateVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtFreeVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ NtQuerySystemInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  RTL_DEBUG_QUERY_HEAPS ; 
 int /*<<< orphan*/  RTL_DEBUG_QUERY_MODULES ; 
 int /*<<< orphan*/ * RtlCreateQueryDebugBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlQueryProcessDebugInformation (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_INFO_LENGTH_MISMATCH ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  SystemProcessInformation ; 
 int TH32CS_SNAPHEAPLIST ; 
 int TH32CS_SNAPMODULE ; 
 int TH32CS_SNAPPROCESS ; 
 int TH32CS_SNAPTHREAD ; 
 int /*<<< orphan*/  TH32FreeAllocatedResources (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static NTSTATUS
TH32CreateSnapshot(DWORD dwFlags,
                   DWORD th32ProcessID,
                   PRTL_DEBUG_INFORMATION *HeapDebug,
                   PRTL_DEBUG_INFORMATION *ModuleDebug,
                   PVOID *ProcThrdInfo,
                   SIZE_T *ProcThrdInfoSize)
{
  NTSTATUS Status = STATUS_SUCCESS;

  *HeapDebug = NULL;
  *ModuleDebug = NULL;
  *ProcThrdInfo = NULL;
  *ProcThrdInfoSize = 0;

  /*
   * Allocate the debug information for a heap snapshot
   */
  if(dwFlags & TH32CS_SNAPHEAPLIST)
  {
    *HeapDebug = RtlCreateQueryDebugBuffer(0, FALSE);
    if(*HeapDebug != NULL)
    {
      Status = RtlQueryProcessDebugInformation(th32ProcessID,
                                               RTL_DEBUG_QUERY_HEAPS,
                                               *HeapDebug);
    }
    else
      Status = STATUS_UNSUCCESSFUL;
  }

  /*
   * Allocate the debug information for a module snapshot
   */
  if(dwFlags & TH32CS_SNAPMODULE &&
     NT_SUCCESS(Status))
  {
    *ModuleDebug = RtlCreateQueryDebugBuffer(0, FALSE);
    if(*ModuleDebug != NULL)
    {
      Status = RtlQueryProcessDebugInformation(th32ProcessID,
                                               RTL_DEBUG_QUERY_MODULES,
                                               *ModuleDebug);
    }
    else
      Status = STATUS_UNSUCCESSFUL;
  }

  /*
   * Allocate enough memory for the system's process list
   */

  if(dwFlags & (TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD) &&
     NT_SUCCESS(Status))
  {
    for(;;)
    {
      (*ProcThrdInfoSize) += 0x10000;
      Status = NtAllocateVirtualMemory(NtCurrentProcess(),
                                       ProcThrdInfo,
                                       0,
                                       ProcThrdInfoSize,
                                       MEM_COMMIT,
                                       PAGE_READWRITE);
      if(!NT_SUCCESS(Status))
      {
        break;
      }

      Status = NtQuerySystemInformation(SystemProcessInformation,
                                        *ProcThrdInfo,
                                        *ProcThrdInfoSize,
                                        NULL);
      if(Status == STATUS_INFO_LENGTH_MISMATCH)
      {
        NtFreeVirtualMemory(NtCurrentProcess(),
                            ProcThrdInfo,
                            ProcThrdInfoSize,
                            MEM_RELEASE);
        *ProcThrdInfo = NULL;
      }
      else
      {
        break;
      }
    }
  }

  /*
   * Free resources in case of failure!
   */

  if(!NT_SUCCESS(Status))
  {
    TH32FreeAllocatedResources(*HeapDebug,
                               *ModuleDebug,
                               *ProcThrdInfo,
                               *ProcThrdInfoSize);
  }

  return Status;
}