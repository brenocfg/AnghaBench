#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut32 ;
struct TYPE_5__ {scalar_t__ e_phoff; scalar_t__ e_machine; scalar_t__ e_phnum; } ;
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  kv; TYPE_1__ ehdr; int /*<<< orphan*/  b; scalar_t__ phdr; } ;
typedef  TYPE_2__ ELFOBJ ;

/* Variables and functions */
 scalar_t__ EM_386 ; 
 scalar_t__ EM_X86_64 ; 
 int /*<<< orphan*/  Elf_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Phdr ; 
 scalar_t__ R_NEWS0 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UT32_MUL (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int const r_buf_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int) ; 
 int /*<<< orphan*/  read_phdr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sdb_num_set (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_phdr(ELFOBJ *bin) {
	ut32 phdr_size;

	r_return_val_if_fail (!bin->phdr, false);

	if (!bin->ehdr.e_phnum) {
		return false;
	}
	if (!UT32_MUL (&phdr_size, (ut32)bin->ehdr.e_phnum, sizeof (Elf_(Phdr)))) {
		return false;
	}
	if (!phdr_size) {
		return false;
	}
	if (phdr_size > bin->size) {
		return false;
	}
	if (phdr_size > (ut32)bin->size) {
		return false;
	}
	if (bin->ehdr.e_phoff > bin->size) {
		return false;
	}
	if (bin->ehdr.e_phoff + phdr_size > bin->size) {
		return false;
	}
	if (!(bin->phdr = R_NEWS0 (Elf_(Phdr), bin->ehdr.e_phnum))) {
		perror ("malloc (phdr)");
		return false;
	}

	bool linux_kern_hack = false;
	/* Enable this hack only for the X86 64bit ELFs */
	const int _128K = 1024 * 128;
	if (r_buf_size (bin->b) > _128K && (bin->ehdr.e_machine == EM_X86_64 || bin->ehdr.e_machine == EM_386)) {
		linux_kern_hack = true;
	}
	if (!read_phdr (bin, linux_kern_hack)) {
		return false;
	}

	sdb_num_set (bin->kv, "elf_phdr.offset", bin->ehdr.e_phoff, 0);
	sdb_num_set (bin->kv, "elf_phdr.size", sizeof (Elf_(Phdr)), 0);
	sdb_set (bin->kv, "elf_p_type.cparse", "enum elf_p_type {PT_NULL=0,PT_LOAD=1,PT_DYNAMIC=2,"
		"PT_INTERP=3,PT_NOTE=4,PT_SHLIB=5,PT_PHDR=6,PT_LOOS=0x60000000,"
		"PT_HIOS=0x6fffffff,PT_LOPROC=0x70000000,PT_HIPROC=0x7fffffff};",
		0);
	sdb_set (bin->kv, "elf_p_flags.cparse", "enum elf_p_flags {PF_None=0,PF_Exec=1,"
			"PF_Write=2,PF_Write_Exec=3,PF_Read=4,PF_Read_Exec=5,PF_Read_Write=6,"
			"PF_Read_Write_Exec=7};", 0);
#if R_BIN_ELF64
	sdb_set (bin->kv, "elf_phdr.format", "[4]E[4]Eqqqqqq (elf_p_type)type (elf_p_flags)flags"
			" offset vaddr paddr filesz memsz align", 0);
#else
	sdb_set (bin->kv, "elf_phdr.format", "[4]Exxxxx[4]Ex (elf_p_type)type offset vaddr paddr"
			" filesz memsz (elf_p_flags)flags align", 0);
#endif
	return true;
	// Usage example:
	// > td `k bin/cur/info/elf_p_type.cparse`; td `k bin/cur/info/elf_p_flags.cparse`
	// > pf `k bin/cur/info/elf_phdr.format` @ `k bin/cur/info/elf_phdr.offset`
}