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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut16 ;

/* Variables and functions */
#define  COFF_FILE_MACHINE_AMD64 132 
#define  COFF_FILE_MACHINE_H8300 131 
#define  COFF_FILE_MACHINE_I386 130 
#define  COFF_FILE_MACHINE_R4000 129 
#define  COFF_FILE_TI_COFF 128 

bool r_coff_supported_arch(const ut8 *buf) {
	ut16 arch = *(ut16*)buf;
	switch (arch) {
	case COFF_FILE_MACHINE_AMD64:
	case COFF_FILE_MACHINE_I386:
	case COFF_FILE_MACHINE_H8300:
	case COFF_FILE_TI_COFF:
	case COFF_FILE_MACHINE_R4000:
		return true;
	default:
		return false;
	}
}