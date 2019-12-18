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

/* Variables and functions */
#define  ORC_TYPE_CALL 130 
#define  ORC_TYPE_REGS 129 
#define  ORC_TYPE_REGS_IRET 128 

__attribute__((used)) static const char *orc_type_name(unsigned int type)
{
	switch (type) {
	case ORC_TYPE_CALL:
		return "call";
	case ORC_TYPE_REGS:
		return "regs";
	case ORC_TYPE_REGS_IRET:
		return "iret";
	default:
		return "?";
	}
}