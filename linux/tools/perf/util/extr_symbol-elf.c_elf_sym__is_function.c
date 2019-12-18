#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ st_name; scalar_t__ st_shndx; } ;
typedef  TYPE_1__ GElf_Sym ;

/* Variables and functions */
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ STT_FUNC ; 
 scalar_t__ STT_GNU_IFUNC ; 
 scalar_t__ elf_sym__type (TYPE_1__ const*) ; 

__attribute__((used)) static inline int elf_sym__is_function(const GElf_Sym *sym)
{
	return (elf_sym__type(sym) == STT_FUNC ||
		elf_sym__type(sym) == STT_GNU_IFUNC) &&
	       sym->st_name != 0 &&
	       sym->st_shndx != SHN_UNDEF;
}