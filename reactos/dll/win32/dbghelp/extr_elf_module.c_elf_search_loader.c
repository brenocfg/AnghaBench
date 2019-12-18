#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct process {int /*<<< orphan*/  handle; } ;
struct elf_info {int dummy; } ;
typedef  int /*<<< orphan*/  pbi ;
typedef  int /*<<< orphan*/  base ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_5__ {TYPE_1__* PebBaseAddress; } ;
struct TYPE_4__ {int /*<<< orphan*/ * Reserved; } ;
typedef  TYPE_2__ PROCESS_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  NtQueryInformationProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessBasicInformation ; 
 int /*<<< orphan*/  ReadProcessMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_search_and_load_file (struct process*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct elf_info*) ; 
 int /*<<< orphan*/  get_wine_loader_name () ; 

__attribute__((used)) static BOOL elf_search_loader(struct process* pcs, struct elf_info* elf_info)
{
    PROCESS_BASIC_INFORMATION pbi;
    ULONG_PTR base = 0;

    if (!NtQueryInformationProcess( pcs->handle, ProcessBasicInformation, &pbi, sizeof(pbi), NULL ))
        ReadProcessMemory( pcs->handle, &pbi.PebBaseAddress->Reserved[0], &base, sizeof(base), NULL );

    return elf_search_and_load_file(pcs, get_wine_loader_name(), base, 0, elf_info);
}