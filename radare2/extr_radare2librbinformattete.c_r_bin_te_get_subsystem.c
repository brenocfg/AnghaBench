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
struct TYPE_2__ {int Subsystem; } ;

/* Variables and functions */
#define  TE_IMAGE_SUBSYSTEM_EFI_APPLICATION 137 
#define  TE_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER 136 
#define  TE_IMAGE_SUBSYSTEM_EFI_ROM 135 
#define  TE_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER 134 
#define  TE_IMAGE_SUBSYSTEM_NATIVE 133 
#define  TE_IMAGE_SUBSYSTEM_POSIX_CUI 132 
#define  TE_IMAGE_SUBSYSTEM_WINDOWS_CE_GUI 131 
#define  TE_IMAGE_SUBSYSTEM_WINDOWS_CUI 130 
#define  TE_IMAGE_SUBSYSTEM_WINDOWS_GUI 129 
#define  TE_IMAGE_SUBSYSTEM_XBOX 128 
 char* strdup (char*) ; 

char* r_bin_te_get_subsystem(struct r_bin_te_obj_t* bin) {
	char *subsystem;

	if (!bin) {
		return NULL;
	}
	switch (bin->header->Subsystem) {
	case TE_IMAGE_SUBSYSTEM_NATIVE:
		subsystem = strdup ("Native");
		break;
	case TE_IMAGE_SUBSYSTEM_WINDOWS_GUI:
		subsystem = strdup ("Windows GUI");
		break;
	case TE_IMAGE_SUBSYSTEM_WINDOWS_CUI:
		subsystem = strdup ("Windows CUI");
		break;
	case TE_IMAGE_SUBSYSTEM_POSIX_CUI:
		subsystem = strdup ("POSIX CUI");
		break;
	case TE_IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:
		subsystem = strdup ("Windows CE GUI");
		break;
	case TE_IMAGE_SUBSYSTEM_EFI_APPLICATION:
		subsystem = strdup ("EFI Application");
		break;
	case TE_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER:
		subsystem = strdup ("EFI Boot Service Driver");
		break;
	case TE_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER:
		subsystem = strdup ("EFI Runtime Driver");
		break;
	case TE_IMAGE_SUBSYSTEM_EFI_ROM:
		subsystem = strdup ("EFI ROM");
		break;
	case TE_IMAGE_SUBSYSTEM_XBOX:
		subsystem = strdup ("XBOX");
		break;
	default:
		subsystem = strdup ("Unknown");
	}
	return subsystem;
}