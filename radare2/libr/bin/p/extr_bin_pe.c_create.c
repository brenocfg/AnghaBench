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
typedef  int ut32 ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinArchOptions ;
typedef  int /*<<< orphan*/  RBin ;

/* Variables and functions */
 int /*<<< orphan*/  B (char const*,int) ; 
 int /*<<< orphan*/  D (int) ; 
 int /*<<< orphan*/  H (int) ; 
 int R_ROUND (int,int) ; 
 int /*<<< orphan*/  W (int,int*,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/ * r_buf_new () ; 
 int r_buf_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static RBuffer* create(RBin* bin, const ut8 *code, int codelen, const ut8 *data, int datalen, RBinArchOptions *opt) {
	ut32 hdrsize, p_start, p_opthdr, p_sections, p_lsrlc, n;
	ut32 baddr = 0x400000;
	RBuffer *buf = r_buf_new ();

#define B(x,y) r_buf_append_bytes(buf,(const ut8*)(x),y)
#define H(x) r_buf_append_ut16(buf,x)
#define D(x) r_buf_append_ut32(buf,x)
#define Z(x) r_buf_append_nbytes(buf,x)
#define W(x,y,z) r_buf_write_at(buf,x,(const ut8*)(y),z)
#define WZ(x,y) p_tmp=r_buf_size (buf);Z(x);W(p_tmp,y,strlen(y))

	B ("MZ\x00\x00", 4); // MZ Header
	B ("PE\x00\x00", 4); // PE Signature
	H (0x14c); // Machine
	H (1); // Number of sections
	D (0); // Timestamp (Unused)
	D (0); // PointerToSymbolTable (Unused)
	D (0); // NumberOfSymbols (Unused)
	p_lsrlc = r_buf_size (buf);
	H (-1); // SizeOfOptionalHeader
	H (0x103); // Characteristics

	/* Optional Header */
	p_opthdr = r_buf_size (buf);
	H (0x10b); // Magic
	B ("\x08\x00", 2); // (Major/Minor)LinkerVersion (Unused)

	p_sections = r_buf_size (buf);
	n = p_sections - p_opthdr;
	W (p_lsrlc, &n, 2); // Fix SizeOfOptionalHeader

	/* Sections */
	p_start = 0x7c; //HACK: Headersize
	hdrsize = 0x7c;

	D (R_ROUND (codelen, 4)); // SizeOfCode (Unused)
	D (0); // SizeOfInitializedData (Unused)
	D (codelen); // codesize
	D (p_start);
	D (codelen);
	D (p_start);
	D (baddr); // ImageBase
	D (4); // SectionAlignment
	D (4); // FileAlignment
	H (4); // MajorOperatingSystemVersion (Unused)
	H (0); // MinorOperatingSystemVersion (Unused)
	H (0); // MajorImageVersion (Unused)
	H (0); // MinorImageVersion (Unused)
	H (4); // MajorSubsystemVersion
	H (0); // MinorSubsystemVersion (Unused)
	D (0); // Win32VersionValue (Unused)
	D ((R_ROUND (hdrsize, 4)) + (R_ROUND (codelen, 4))); // SizeOfImage
	D (R_ROUND (hdrsize, 4)); // SizeOfHeaders
	D (0); // CheckSum (Unused)
	H (2); // Subsystem (Win32 GUI)
	H (0x400); // DllCharacteristics (Unused)
	D (0x100000); // SizeOfStackReserve (Unused)
	D (0x1000); // SizeOfStackCommit
	D (0x100000); // SizeOfHeapReserve
	D (0x1000); // SizeOfHeapCommit (Unused)
	D (0); // LoaderFlags (Unused)
	D (0); // NumberOfRvaAndSizes (Unused)
	B (code, codelen);

	if (data && datalen>0) {
		//ut32 data_section = buf->length;
		eprintf ("Warning: DATA section not support for PE yet\n");
		B (data, datalen);
	}
	return buf;
}