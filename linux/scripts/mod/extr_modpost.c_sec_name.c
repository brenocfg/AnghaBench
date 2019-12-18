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
struct elf_info {int /*<<< orphan*/ * sechdrs; } ;

/* Variables and functions */
 char const* sech_name (struct elf_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *sec_name(struct elf_info *elf, int secindex)
{
	return sech_name(elf, &elf->sechdrs[secindex]);
}