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
typedef  int /*<<< orphan*/  GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Data ;

/* Variables and functions */
 scalar_t__ elf_sec__is_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ elf_sec__is_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool elf_sec__filter(GElf_Shdr *shdr, Elf_Data *secstrs)
{
	return elf_sec__is_text(shdr, secstrs) || 
	       elf_sec__is_data(shdr, secstrs);
}