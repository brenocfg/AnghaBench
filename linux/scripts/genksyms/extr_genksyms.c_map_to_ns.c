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
#define  SYM_ENUM 133 
#define  SYM_ENUM_CONST 132 
#define  SYM_NORMAL 131 
#define  SYM_STRUCT 130 
#define  SYM_TYPEDEF 129 
#define  SYM_UNION 128 

__attribute__((used)) static enum symbol_type map_to_ns(enum symbol_type t)
{
	switch (t) {
	case SYM_ENUM_CONST:
	case SYM_NORMAL:
	case SYM_TYPEDEF:
		return SYM_NORMAL;
	case SYM_ENUM:
	case SYM_STRUCT:
	case SYM_UNION:
		return SYM_STRUCT;
	}
	return t;
}