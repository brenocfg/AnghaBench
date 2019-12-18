#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct process {int /*<<< orphan*/  handle; scalar_t__ dbg_hdr_addr; } ;
struct module {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  CheckSum; scalar_t__ SizeOfImage; } ;
struct TYPE_6__ {int /*<<< orphan*/  TimeDateStamp; } ;
struct TYPE_7__ {TYPE_1__ OptionalHeader; TYPE_2__ FileHeader; } ;
typedef  TYPE_3__ IMAGE_NT_HEADERS ;
typedef  scalar_t__ DWORD64 ;

/* Variables and functions */
 int /*<<< orphan*/  DMT_PE ; 
 int /*<<< orphan*/  FALSE ; 
 struct module* module_new (struct process*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pe_load_nt_header (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 

struct module* pe_load_builtin_module(struct process* pcs, const WCHAR* name,
                                      DWORD64 base, DWORD64 size)
{
    struct module*      module = NULL;

    if (base && pcs->dbg_hdr_addr)
    {
        IMAGE_NT_HEADERS    nth;

        if (pe_load_nt_header(pcs->handle, base, &nth))
        {
            if (!size) size = nth.OptionalHeader.SizeOfImage;
            module = module_new(pcs, name, DMT_PE, FALSE, base, size,
                                nth.FileHeader.TimeDateStamp,
                                nth.OptionalHeader.CheckSum);
        }
    }
    return module;
}