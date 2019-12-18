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
#define  TE_IMAGE_FILE_MACHINE_ALPHA 155 
#define  TE_IMAGE_FILE_MACHINE_ALPHA64 154 
#define  TE_IMAGE_FILE_MACHINE_AM33 153 
#define  TE_IMAGE_FILE_MACHINE_AMD64 152 
#define  TE_IMAGE_FILE_MACHINE_ARM 151 
#define  TE_IMAGE_FILE_MACHINE_CEE 150 
#define  TE_IMAGE_FILE_MACHINE_CEF 149 
#define  TE_IMAGE_FILE_MACHINE_EBC 148 
#define  TE_IMAGE_FILE_MACHINE_I386 147 
#define  TE_IMAGE_FILE_MACHINE_IA64 146 
#define  TE_IMAGE_FILE_MACHINE_M32R 145 
#define  TE_IMAGE_FILE_MACHINE_M68K 144 
#define  TE_IMAGE_FILE_MACHINE_MIPS16 143 
#define  TE_IMAGE_FILE_MACHINE_MIPSFPU 142 
#define  TE_IMAGE_FILE_MACHINE_MIPSFPU16 141 
#define  TE_IMAGE_FILE_MACHINE_POWERPC 140 
#define  TE_IMAGE_FILE_MACHINE_POWERPCFP 139 
#define  TE_IMAGE_FILE_MACHINE_R10000 138 
#define  TE_IMAGE_FILE_MACHINE_R3000 137 
#define  TE_IMAGE_FILE_MACHINE_R4000 136 
#define  TE_IMAGE_FILE_MACHINE_SH3 135 
#define  TE_IMAGE_FILE_MACHINE_SH3DSP 134 
#define  TE_IMAGE_FILE_MACHINE_SH3E 133 
#define  TE_IMAGE_FILE_MACHINE_SH4 132 
#define  TE_IMAGE_FILE_MACHINE_SH5 131 
#define  TE_IMAGE_FILE_MACHINE_THUMB 130 
#define  TE_IMAGE_FILE_MACHINE_TRICORE 129 
#define  TE_IMAGE_FILE_MACHINE_WCEMIPSV2 128 
 char* strdup (char*) ; 

char* r_bin_te_get_machine(struct r_bin_te_obj_t* bin) {
	char *machine;
	if (!bin) {
		return NULL;
	}
	switch (bin->header->Machine) {
	case TE_IMAGE_FILE_MACHINE_ALPHA:
		machine = strdup ("Alpha");
		break;
	case TE_IMAGE_FILE_MACHINE_ALPHA64:
		machine = strdup ("Alpha 64");
		break;
	case TE_IMAGE_FILE_MACHINE_AM33:
		machine = strdup ("AM33");
		break;
	case TE_IMAGE_FILE_MACHINE_AMD64:
		machine = strdup ("AMD 64");
		break;
	case TE_IMAGE_FILE_MACHINE_ARM:
		machine = strdup ("ARM");
		break;
	case TE_IMAGE_FILE_MACHINE_CEE:
		machine = strdup ("CEE");
		break;
	case TE_IMAGE_FILE_MACHINE_CEF:
		machine = strdup ("CEF");
		break;
	case TE_IMAGE_FILE_MACHINE_EBC:
		machine = strdup ("EBC");
		break;
	case TE_IMAGE_FILE_MACHINE_I386:
		machine = strdup ("i386");
		break;
	case TE_IMAGE_FILE_MACHINE_IA64:
		machine = strdup ("ia64");
		break;
	case TE_IMAGE_FILE_MACHINE_M32R:
		machine = strdup ("M32R");
		break;
	case TE_IMAGE_FILE_MACHINE_M68K:
		machine = strdup ("M68K");
		break;
	case TE_IMAGE_FILE_MACHINE_MIPS16:
		machine = strdup ("Mips 16");
		break;
	case TE_IMAGE_FILE_MACHINE_MIPSFPU:
		machine = strdup ("Mips FPU");
		break;
	case TE_IMAGE_FILE_MACHINE_MIPSFPU16:
		machine = strdup ("Mips FPU 16");
		break;
	case TE_IMAGE_FILE_MACHINE_POWERPC:
		machine = strdup ("PowerPC");
		break;
	case TE_IMAGE_FILE_MACHINE_POWERPCFP:
		machine = strdup ("PowerPC FP");
		break;
	case TE_IMAGE_FILE_MACHINE_R10000:
		machine = strdup ("R10000");
		break;
	case TE_IMAGE_FILE_MACHINE_R3000:
		machine = strdup ("R3000");
		break;
	case TE_IMAGE_FILE_MACHINE_R4000:
		machine = strdup ("R4000");
		break;
	case TE_IMAGE_FILE_MACHINE_SH3:
		machine = strdup ("SH3");
		break;
	case TE_IMAGE_FILE_MACHINE_SH3DSP:
		machine = strdup ("SH3DSP");
		break;
	case TE_IMAGE_FILE_MACHINE_SH3E:
		machine = strdup ("SH3E");
		break;
	case TE_IMAGE_FILE_MACHINE_SH4:
		machine = strdup ("SH4");
		break;
	case TE_IMAGE_FILE_MACHINE_SH5:
		machine = strdup ("SH5");
		break;
	case TE_IMAGE_FILE_MACHINE_THUMB:
		machine = strdup ("Thumb");
		break;
	case TE_IMAGE_FILE_MACHINE_TRICORE:
		machine = strdup ("Tricore");
		break;
	case TE_IMAGE_FILE_MACHINE_WCEMIPSV2:
		machine = strdup ("WCE Mips V2");
		break;
	default:
		machine = strdup ("unknown");
	}
	return machine;
}