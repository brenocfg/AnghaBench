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
struct elf_info {char* ksymtab_strings; } ;
struct TYPE_3__ {int st_value; } ;
typedef  TYPE_1__ Elf_Sym ;

/* Variables and functions */

__attribute__((used)) static const char *namespace_from_kstrtabns(struct elf_info *info,
					    Elf_Sym *kstrtabns)
{
	char *value = info->ksymtab_strings + kstrtabns->st_value;
	return value[0] ? value : NULL;
}