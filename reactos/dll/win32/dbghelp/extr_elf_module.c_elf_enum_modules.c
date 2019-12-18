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
struct process {int /*<<< orphan*/  dbg_hdr_addr; int /*<<< orphan*/  handle; } ;
struct elf_info {int flags; scalar_t__ module_name; int /*<<< orphan*/  dbg_hdr_addr; } ;
struct elf_enum_user {void* user; int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  pcs ;
typedef  int /*<<< orphan*/  enum_modules_cb ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ELF_INFO_DEBUG_HEADER ; 
 int ELF_INFO_NAME ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  elf_enum_modules_internal (struct process*,scalar_t__,int /*<<< orphan*/ ,struct elf_enum_user*) ; 
 int /*<<< orphan*/  elf_enum_modules_translate ; 
 int /*<<< orphan*/  elf_search_loader (struct process*,struct elf_info*) ; 
 int /*<<< orphan*/  memset (struct process*,int /*<<< orphan*/ ,int) ; 

BOOL elf_enum_modules(HANDLE hProc, enum_modules_cb cb, void* user)
{
    struct process      pcs;
    struct elf_info     elf_info;
    BOOL                ret;
    struct elf_enum_user eeu;

    memset(&pcs, 0, sizeof(pcs));
    pcs.handle = hProc;
    elf_info.flags = ELF_INFO_DEBUG_HEADER | ELF_INFO_NAME;
    if (!elf_search_loader(&pcs, &elf_info)) return FALSE;
    pcs.dbg_hdr_addr = elf_info.dbg_hdr_addr;
    eeu.cb = cb;
    eeu.user = user;
    ret = elf_enum_modules_internal(&pcs, elf_info.module_name, elf_enum_modules_translate, &eeu);
    HeapFree(GetProcessHeap(), 0, (char*)elf_info.module_name);
    return ret;
}