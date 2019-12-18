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
typedef  char ut8 ;
typedef  int ut64 ;
typedef  int ut32 ;
typedef  int ut16 ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinArchOptions ;
typedef  int /*<<< orphan*/  RBin ;

/* Variables and functions */
 int /*<<< orphan*/  B (char const*,int) ; 
 int /*<<< orphan*/  D (int) ; 
 int /*<<< orphan*/  H (int) ; 
 int /*<<< orphan*/  Q (int) ; 
 int /*<<< orphan*/  W (int,int*,int) ; 
 int /*<<< orphan*/  Z (int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/ * r_buf_new () ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static RBuffer* create(RBin* bin, const ut8 *code, int codelen, const ut8 *data, int datalen, RBinArchOptions *opt) {
	ut32 p_start, p_phoff, p_phdr;
	ut32 p_vaddr, p_paddr, p_fs, p_fs2;
	ut32 p_ehdrsz, p_phdrsz;
	ut64 filesize, code_va, code_pa, phoff;
	ut16 ehdrsz, phdrsz;
	ut64 baddr = 0x400000LL;
	RBuffer *buf = r_buf_new ();

#define B(x,y) r_buf_append_bytes(buf,(const ut8*)(x),y)
#define Q(x) r_buf_append_ut64(buf,x)
#define D(x) r_buf_append_ut32(buf,x)
#define H(x) r_buf_append_ut16(buf,x)
#define Z(x) r_buf_append_nbytes(buf,x)
#define W(x,y,z) r_buf_write_at(buf,x,(const ut8*)(y),z)

	/* Ehdr */
	B ("\x7F" "ELF" "\x02\x01\x01\x00", 8); // e_ident (ei_class = ELFCLASS64)
	Z (8);
	H (2); // e_type = ET_EXEC
	H (62); // e_machine = EM_X86_64
	D (1); // e_version = EV_CURRENT
	p_start = r_buf_size (buf);
	Q (-1); // e_entry = 0xFFFFFFFF
	p_phoff = r_buf_size (buf);
	Q (-1); // e_phoff = 0xFFFFFFFF
	Q (0);  // e_shoff = 0xFFFFFFFF
	D (0);  // e_flags
	p_ehdrsz = r_buf_size (buf);
	H (-1); // e_ehsize = 0xFFFFFFFF
	p_phdrsz = r_buf_size (buf);
	H (-1); // e_phentsize = 0xFFFFFFFF
	H (1);  // e_phnum
	H (0);  // e_shentsize
	H (0);  // e_shnum
	H (0);  // e_shstrndx

	/* Phdr */
	p_phdr = r_buf_size (buf);
	D (1); // p_type
	D (5);  // p_flags = PF_R | PF_X
	Q (0);  // p_offset
	p_vaddr = r_buf_size (buf);
	Q (-1); // p_vaddr = 0xFFFFFFFF
	p_paddr = r_buf_size (buf);
	Q (-1); // p_paddr = 0xFFFFFFFF
	p_fs = r_buf_size (buf);
	Q (-1); // p_filesz
	p_fs2 = r_buf_size (buf);
	Q (-1); // p_memsz
	Q (0x200000); // p_align

	/* Calc fields */
	ehdrsz = p_phdr;
	phdrsz = r_buf_size (buf) - p_phdr;
	code_pa = r_buf_size (buf);
	code_va = code_pa + baddr;
	phoff = p_phdr;
	filesize = code_pa + codelen + datalen;

	/* Write fields */
	W (p_start, &code_va, 8);
	W (p_phoff, &phoff, 8);
	W (p_ehdrsz, &ehdrsz, 2);
	W (p_phdrsz, &phdrsz, 2);
	W (p_fs, &filesize, 8);
	W (p_fs2, &filesize, 8);

	W (p_vaddr, &baddr, 8);
	W (p_paddr, &baddr, 8);

	/* Append code */
	B (code, codelen);

	if (data && datalen>0) {
		eprintf ("Warning: DATA section not support for ELF yet\n");
		B (data, datalen);
	}
	return buf;
}