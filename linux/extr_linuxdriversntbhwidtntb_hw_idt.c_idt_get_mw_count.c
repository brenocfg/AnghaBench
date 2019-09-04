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
typedef  enum idt_mw_type { ____Placeholder_idt_mw_type } idt_mw_type ;

/* Variables and functions */
#define  IDT_MW_DIR 130 
#define  IDT_MW_LUT12 129 
#define  IDT_MW_LUT24 128 

__attribute__((used)) static inline unsigned char idt_get_mw_count(enum idt_mw_type mw_type)
{
	switch (mw_type) {
	case IDT_MW_DIR:
		return 1;
	case IDT_MW_LUT12:
		return 12;
	case IDT_MW_LUT24:
		return 24;
	default:
		break;
	}

	return 0;
}