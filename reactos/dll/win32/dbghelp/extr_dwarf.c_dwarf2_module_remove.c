#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct process {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dwarf2_info; } ;
struct module_format {TYPE_2__ u; } ;
struct TYPE_3__ {int /*<<< orphan*/  debug_frame; int /*<<< orphan*/  debug_loc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_format*) ; 
 int /*<<< orphan*/  dwarf2_fini_section (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwarf2_module_remove(struct process* pcs, struct module_format* modfmt)
{
    dwarf2_fini_section(&modfmt->u.dwarf2_info->debug_loc);
    dwarf2_fini_section(&modfmt->u.dwarf2_info->debug_frame);
    HeapFree(GetProcessHeap(), 0, modfmt);
}