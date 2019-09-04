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
typedef  int /*<<< orphan*/  GElf_Sym ;

/* Variables and functions */
 scalar_t__ elf_sym__is_function (int /*<<< orphan*/ *) ; 
 scalar_t__ elf_sym__is_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool elf_sym__filter(GElf_Sym *sym)
{
	return elf_sym__is_function(sym) || elf_sym__is_object(sym);
}