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
struct megasas_instance {void* adapter_type; TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ vendor; int device; } ;

/* Variables and functions */
 void* INVADER_SERIES ; 
 void* MFI_SERIES ; 
 int PCI_DEVICE_ID_DELL_PERC5 ; 
#define  PCI_DEVICE_ID_LSI_CRUSADER 141 
#define  PCI_DEVICE_ID_LSI_CRUSADER_4PORT 140 
#define  PCI_DEVICE_ID_LSI_CUTLASS_52 139 
#define  PCI_DEVICE_ID_LSI_CUTLASS_53 138 
#define  PCI_DEVICE_ID_LSI_FURY 137 
#define  PCI_DEVICE_ID_LSI_FUSION 136 
#define  PCI_DEVICE_ID_LSI_HARPOON 135 
#define  PCI_DEVICE_ID_LSI_INTRUDER 134 
#define  PCI_DEVICE_ID_LSI_INTRUDER_24 133 
#define  PCI_DEVICE_ID_LSI_INVADER 132 
#define  PCI_DEVICE_ID_LSI_PLASMA 131 
#define  PCI_DEVICE_ID_LSI_TOMCAT 130 
#define  PCI_DEVICE_ID_LSI_VENTURA 129 
#define  PCI_DEVICE_ID_LSI_VENTURA_4PORT 128 
 scalar_t__ PCI_VENDOR_ID_DELL ; 
 void* THUNDERBOLT_SERIES ; 
 void* VENTURA_SERIES ; 

__attribute__((used)) static inline void megasas_set_adapter_type(struct megasas_instance *instance)
{
	if ((instance->pdev->vendor == PCI_VENDOR_ID_DELL) &&
	    (instance->pdev->device == PCI_DEVICE_ID_DELL_PERC5)) {
		instance->adapter_type = MFI_SERIES;
	} else {
		switch (instance->pdev->device) {
		case PCI_DEVICE_ID_LSI_VENTURA:
		case PCI_DEVICE_ID_LSI_CRUSADER:
		case PCI_DEVICE_ID_LSI_HARPOON:
		case PCI_DEVICE_ID_LSI_TOMCAT:
		case PCI_DEVICE_ID_LSI_VENTURA_4PORT:
		case PCI_DEVICE_ID_LSI_CRUSADER_4PORT:
			instance->adapter_type = VENTURA_SERIES;
			break;
		case PCI_DEVICE_ID_LSI_FUSION:
		case PCI_DEVICE_ID_LSI_PLASMA:
			instance->adapter_type = THUNDERBOLT_SERIES;
			break;
		case PCI_DEVICE_ID_LSI_INVADER:
		case PCI_DEVICE_ID_LSI_INTRUDER:
		case PCI_DEVICE_ID_LSI_INTRUDER_24:
		case PCI_DEVICE_ID_LSI_CUTLASS_52:
		case PCI_DEVICE_ID_LSI_CUTLASS_53:
		case PCI_DEVICE_ID_LSI_FURY:
			instance->adapter_type = INVADER_SERIES;
			break;
		default: /* For all other supported controllers */
			instance->adapter_type = MFI_SERIES;
			break;
		}
	}
}