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
struct TYPE_3__ {scalar_t__* e_ident; int e_flags; } ;
typedef  TYPE_1__ Elf_Internal_Ehdr ;

/* Variables and functions */
 int EF_MIPS_ABI2 ; 
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS64 ; 

__attribute__((used)) static int
is_newabi (Elf_Internal_Ehdr *header)
{
  /* There are no old-style ABIs which use 64-bit ELF.  */
  if (header->e_ident[EI_CLASS] == ELFCLASS64) {
	  return 1;
  }

  /* If a 32-bit ELF file, n32 is a new-style ABI.  */
  if ((header->e_flags & EF_MIPS_ABI2) != 0) {
	  return 1;
  }

  return 0;
}