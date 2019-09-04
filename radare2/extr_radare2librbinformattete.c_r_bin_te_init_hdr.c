#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct r_bin_te_obj_t {TYPE_1__* header; int /*<<< orphan*/  kv; int /*<<< orphan*/  b; } ;
struct TYPE_2__ {int /*<<< orphan*/  Signature; } ;
typedef  int /*<<< orphan*/  TE_image_file_header ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 TYPE_1__* malloc (int) ; 
 int r_buf_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 int /*<<< orphan*/  sdb_num_set (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int r_bin_te_init_hdr(struct r_bin_te_obj_t *bin) {
	if (!bin) {
		return false;
	}
	if (!(bin->header = malloc (sizeof(TE_image_file_header)))) {
		r_sys_perror ("malloc (header)");
		return false;
	}
	if (r_buf_read_at (bin->b, 0, (ut8*)bin->header, sizeof (TE_image_file_header)) == -1) {
		eprintf("Error: read (header)\n");
		return false;
	}
	if (!bin->kv) {
		eprintf("Error: sdb instance is empty\n");
		return false;
	}

	sdb_set (bin->kv, "te_machine.cparse", "enum te_machine { TE_IMAGE_FILE_MACHINE_UNKNOWN=0x0, TE_IMAGE_FILE_MACHINE_ALPHA=0x184, "
	"TE_IMAGE_FILE_MACHINE_ALPHA64=0x284, TE_IMAGE_FILE_MACHINE_AM33=0x1d3, TE_IMAGE_FILE_MACHINE_AMD64=0x8664, "
	"TE_IMAGE_FILE_MACHINE_ARM=0x1c0, TE_IMAGE_FILE_MACHINE_AXP64=0x184, TE_IMAGE_FILE_MACHINE_CEE=0xc0ee, "
	"TE_IMAGE_FILE_MACHINE_CEF=0x0cef, TE_IMAGE_FILE_MACHINE_EBC=0x0ebc, TE_IMAGE_FILE_MACHINE_I386=0x014c, "
	"TE_IMAGE_FILE_MACHINE_IA64=0x0200, TE_IMAGE_FILE_MACHINE_M32R=0x9041, TE_IMAGE_FILE_MACHINE_M68K=0x0268, "
	"TE_IMAGE_FILE_MACHINE_MIPS16=0x0266, TE_IMAGE_FILE_MACHINE_MIPSFPU=0x0366, TE_IMAGE_FILE_MACHINE_MIPSFPU16=0x0466, "
	"TE_IMAGE_FILE_MACHINE_POWERPC=0x01f0, TE_IMAGE_FILE_MACHINE_POWERPCFP=0x01f1, TE_IMAGE_FILE_MACHINE_R10000=0x0168, "
	"TE_IMAGE_FILE_MACHINE_R3000=0x0162, TE_IMAGE_FILE_MACHINE_R4000=0x0166, TE_IMAGE_FILE_MACHINE_SH3=0x01a2, "
	"TE_IMAGE_FILE_MACHINE_SH3DSP=0x01a3, TE_IMAGE_FILE_MACHINE_SH3E=0x01a4, TE_IMAGE_FILE_MACHINE_SH4=0x01a6, "
	"TE_IMAGE_FILE_MACHINE_SH5=0x01a8, TE_IMAGE_FILE_MACHINE_THUMB=0x01c2, TE_IMAGE_FILE_MACHINE_TRICORE=0x0520, "
	"TE_IMAGE_FILE_MACHINE_WCEMIPSV2=0x0169};", 0);
	sdb_set (bin->kv, "te_subsystem.cparse", "enum te_subsystem { TE_IMAGE_SUBSYSTEM_UNKNOWN=0, TE_IMAGE_SUBSYSTEM_NATIVE=1, "
	"TE_IMAGE_SUBSYSTEM_WINDOWS_GUI=2, TE_IMAGE_SUBSYSTEM_WINDOWS_CUI=3, "
	"TE_IMAGE_SUBSYSTEM_POSIX_CUI=7, TE_IMAGE_SUBSYSTEM_WINDOWS_CE_GU=9, "
	"TE_IMAGE_SUBSYSTEM_EFI_APPLICATION=10, TE_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER=11, TE_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER=12, "
	"TE_IMAGE_SUBSYSTEM_EFI_ROM=13, TE_IMAGE_SUBSYSTEM_XBOX=14};", 0);
	sdb_num_set (bin->kv, "te_header.offset", 0, 0);
	sdb_set (bin->kv, "te_header.format", "[2]z[2]Eb[1]Ewxxq"
		" Signature (te_machine)Machine NumberOfSections (te_subsystem)Subsystem StrippedSize AddressOfEntryPoint BaseOfCode ImageBase", 0);
	sdb_num_set (bin->kv, "te_directory1_header.offset", 24, 0);
	sdb_set (bin->kv, "te_directory1_header.format", "xx"
		" VirtualAddress Size", 0);
	sdb_num_set (bin->kv, "te_directory2_header.offset", 32, 0);
	sdb_set (bin->kv, "te_directory2_header.format", "xx"
		" VirtualAddress Size", 0);

	if (strncmp ((char *)&bin->header->Signature, "VZ", 2)) {
		return false;
	}
	return true;
}