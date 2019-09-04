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
typedef  enum bpf_reg_type { ____Placeholder_bpf_reg_type } bpf_reg_type ;

/* Variables and functions */
#define  CONST_PTR_TO_MAP 135 
#define  PTR_TO_CTX 134 
#define  PTR_TO_MAP_VALUE 133 
#define  PTR_TO_MAP_VALUE_OR_NULL 132 
#define  PTR_TO_PACKET 131 
#define  PTR_TO_PACKET_END 130 
#define  PTR_TO_PACKET_META 129 
#define  PTR_TO_STACK 128 

__attribute__((used)) static bool is_spillable_regtype(enum bpf_reg_type type)
{
	switch (type) {
	case PTR_TO_MAP_VALUE:
	case PTR_TO_MAP_VALUE_OR_NULL:
	case PTR_TO_STACK:
	case PTR_TO_CTX:
	case PTR_TO_PACKET:
	case PTR_TO_PACKET_META:
	case PTR_TO_PACKET_END:
	case CONST_PTR_TO_MAP:
		return true;
	default:
		return false;
	}
}