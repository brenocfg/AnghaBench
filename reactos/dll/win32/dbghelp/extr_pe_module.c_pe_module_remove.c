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
struct TYPE_4__ {TYPE_1__* pe_info; } ;
struct module_format {TYPE_2__ u; } ;
struct TYPE_3__ {int /*<<< orphan*/  fmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_format*) ; 
 int /*<<< orphan*/  pe_unmap_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pe_module_remove(struct process* pcs, struct module_format* modfmt)
{
    pe_unmap_file(&modfmt->u.pe_info->fmap);
    HeapFree(GetProcessHeap(), 0, modfmt);
}