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
typedef  int ut8 ;

/* Variables and functions */
#define  WIRE_32_BIT 133 
#define  WIRE_64_BIT 132 
#define  WIRE_END_GRP 131 
#define  WIRE_LEN_DELIM 130 
#define  WIRE_START_GRP 129 
#define  WIRE_VARINT 128 

__attribute__((used)) static const char* s_wire(const ut8 byte) {
	switch (byte) {
	case WIRE_VARINT:
		return "[VARINT]";
	case WIRE_64_BIT:
		return "[64_BIT]";
	case WIRE_LEN_DELIM:
		return "[LEN_DELIM]";
	case WIRE_START_GRP:
		return "[START_GROUP]";
	case WIRE_END_GRP:
		return "[END_GROUP]";
	case WIRE_32_BIT:
		return "[32_BIT]";
	default:
		return "[UNKN]";
	}
}