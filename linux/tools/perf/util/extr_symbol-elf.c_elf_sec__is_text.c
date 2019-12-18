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
 int /*<<< orphan*/  elf_sec__name (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int elf_sec__is_text(const GElf_Shdr *shdr,
					const Elf_Data *secstrs)
{
	return strstr(elf_sec__name(shdr, secstrs), "text") != NULL;
}