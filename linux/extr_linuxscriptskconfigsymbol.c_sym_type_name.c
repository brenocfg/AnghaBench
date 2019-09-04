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
typedef  enum symbol_type { ____Placeholder_symbol_type } symbol_type ;

/* Variables and functions */
#define  S_BOOLEAN 134 
#define  S_HEX 133 
#define  S_INT 132 
#define  S_OTHER 131 
#define  S_STRING 130 
#define  S_TRISTATE 129 
#define  S_UNKNOWN 128 

const char *sym_type_name(enum symbol_type type)
{
	switch (type) {
	case S_BOOLEAN:
		return "bool";
	case S_TRISTATE:
		return "tristate";
	case S_INT:
		return "integer";
	case S_HEX:
		return "hex";
	case S_STRING:
		return "string";
	case S_UNKNOWN:
		return "unknown";
	case S_OTHER:
		break;
	}
	return "???";
}