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
struct comedi_device {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 unsigned int NI_PFI_OUTPUT_AI_CONVERT ; 
 unsigned int NI_PFI_OUTPUT_AI_START1 ; 
 unsigned int NI_PFI_OUTPUT_AI_START2 ; 
 unsigned int NI_PFI_OUTPUT_AI_START_PULSE ; 
 unsigned int NI_PFI_OUTPUT_AO_START1 ; 
 unsigned int NI_PFI_OUTPUT_AO_UPDATE_N ; 
 unsigned int NI_PFI_OUTPUT_G_GATE0 ; 
 unsigned int NI_PFI_OUTPUT_G_GATE1 ; 
 unsigned int NI_PFI_OUTPUT_G_SRC0 ; 
 unsigned int NI_PFI_OUTPUT_G_SRC1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static unsigned int ni_old_get_pfi_routing(struct comedi_device *dev,
					   unsigned int chan)
{
	/*  pre-m-series boards have fixed signals on pfi pins */
	switch (chan) {
	case 0:
		return NI_PFI_OUTPUT_AI_START1;
	case 1:
		return NI_PFI_OUTPUT_AI_START2;
	case 2:
		return NI_PFI_OUTPUT_AI_CONVERT;
	case 3:
		return NI_PFI_OUTPUT_G_SRC1;
	case 4:
		return NI_PFI_OUTPUT_G_GATE1;
	case 5:
		return NI_PFI_OUTPUT_AO_UPDATE_N;
	case 6:
		return NI_PFI_OUTPUT_AO_START1;
	case 7:
		return NI_PFI_OUTPUT_AI_START_PULSE;
	case 8:
		return NI_PFI_OUTPUT_G_SRC0;
	case 9:
		return NI_PFI_OUTPUT_G_GATE0;
	default:
		dev_err(dev->class_dev, "bug, unhandled case in switch.\n");
		break;
	}
	return 0;
}