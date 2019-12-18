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
struct r_bin_te_obj_t {TYPE_1__* header; } ;
struct TYPE_2__ {int Machine; } ;

/* Variables and functions */
#define  TE_IMAGE_FILE_MACHINE_ALPHA 138 
#define  TE_IMAGE_FILE_MACHINE_ALPHA64 137 
#define  TE_IMAGE_FILE_MACHINE_ARM 136 
#define  TE_IMAGE_FILE_MACHINE_M68K 135 
#define  TE_IMAGE_FILE_MACHINE_MIPS16 134 
#define  TE_IMAGE_FILE_MACHINE_MIPSFPU 133 
#define  TE_IMAGE_FILE_MACHINE_MIPSFPU16 132 
#define  TE_IMAGE_FILE_MACHINE_POWERPC 131 
#define  TE_IMAGE_FILE_MACHINE_POWERPCFP 130 
#define  TE_IMAGE_FILE_MACHINE_THUMB 129 
#define  TE_IMAGE_FILE_MACHINE_WCEMIPSV2 128 
 char* strdup (char*) ; 

char* r_bin_te_get_arch(struct r_bin_te_obj_t* bin) {
	char *arch;
	if (!bin) {
		return NULL;
	}
	switch (bin->header->Machine) {
	case TE_IMAGE_FILE_MACHINE_ALPHA:
	case TE_IMAGE_FILE_MACHINE_ALPHA64:
		arch = strdup ("alpha");
		break;
	case TE_IMAGE_FILE_MACHINE_ARM:
	case TE_IMAGE_FILE_MACHINE_THUMB:
		arch = strdup ("arm");
		break;
	case TE_IMAGE_FILE_MACHINE_M68K:
		arch = strdup ("m68k");
		break;
	case TE_IMAGE_FILE_MACHINE_MIPS16:
	case TE_IMAGE_FILE_MACHINE_MIPSFPU:
	case TE_IMAGE_FILE_MACHINE_MIPSFPU16:
	case TE_IMAGE_FILE_MACHINE_WCEMIPSV2:
		arch = strdup ("mips");
		break;
	case TE_IMAGE_FILE_MACHINE_POWERPC:
	case TE_IMAGE_FILE_MACHINE_POWERPCFP:
		arch = strdup ("ppc");
		break;
	default:
		arch = strdup ("x86");
	}
	return arch;
}