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
typedef  int /*<<< orphan*/  u64 ;
struct kcore {int /*<<< orphan*/  elf; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int p_flags; int /*<<< orphan*/  p_align; int /*<<< orphan*/  p_memsz; int /*<<< orphan*/  p_filesz; int /*<<< orphan*/  p_paddr; int /*<<< orphan*/  p_vaddr; int /*<<< orphan*/  p_offset; int /*<<< orphan*/  p_type; } ;
typedef  TYPE_1__ GElf_Phdr ;

/* Variables and functions */
 int PF_R ; 
 int PF_W ; 
 int PF_X ; 
 int /*<<< orphan*/  PT_LOAD ; 
 int /*<<< orphan*/  gelf_update_phdr (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  page_size ; 

__attribute__((used)) static int kcore__add_phdr(struct kcore *kcore, int idx, off_t offset,
			   u64 addr, u64 len)
{
	GElf_Phdr phdr = {
		.p_type		= PT_LOAD,
		.p_flags	= PF_R | PF_W | PF_X,
		.p_offset	= offset,
		.p_vaddr	= addr,
		.p_paddr	= 0,
		.p_filesz	= len,
		.p_memsz	= len,
		.p_align	= page_size,
	};

	if (!gelf_update_phdr(kcore->elf, idx, &phdr))
		return -1;

	return 0;
}