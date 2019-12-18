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
typedef  int arm64_extender ;

/* Variables and functions */
#define  ARM64_EXT_SXTB 135 
#define  ARM64_EXT_SXTH 134 
#define  ARM64_EXT_SXTW 133 
#define  ARM64_EXT_SXTX 132 
#define  ARM64_EXT_UXTB 131 
#define  ARM64_EXT_UXTH 130 
#define  ARM64_EXT_UXTW 129 
#define  ARM64_EXT_UXTX 128 

__attribute__((used)) static const char *extender_name(arm64_extender extender) {
	switch (extender) {
	case ARM64_EXT_UXTB:
		return "uxtb";
	case ARM64_EXT_UXTH:
		return "uxth";
	case ARM64_EXT_UXTW:
		return "uxtw";
	case ARM64_EXT_UXTX:
		return "uxtx";
	case ARM64_EXT_SXTB:
		return "sxtb";
	case ARM64_EXT_SXTH:
		return "sxth";
	case ARM64_EXT_SXTW:
		return "sxtw";
	case ARM64_EXT_SXTX:
		return "sxtx";
	default:
		return "";
	}
}