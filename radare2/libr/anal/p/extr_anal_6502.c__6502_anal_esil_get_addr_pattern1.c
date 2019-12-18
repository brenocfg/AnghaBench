#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_3__ {int cycles; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int const) ; 

__attribute__((used)) static void _6502_anal_esil_get_addr_pattern1(RAnalOp *op, const ut8* data, int len, char* addrbuf, int addrsize) {
	if (len < 1) {
		return;
	}
	// turn off bits 5, 6 and 7
	switch (data[0] & 0x1f) { // 0x1f = b00111111
	case 0x09: // op #$ff
		op->cycles = 2;
		snprintf (addrbuf, addrsize,"0x%02x", (len > 1)? data[1]: 0);
		break;
	case 0x05: // op $ff
		op->cycles = 3;
		snprintf (addrbuf, addrsize,"0x%02x", (len > 1)? data[1]: 0);
		break;
	case 0x15: // op $ff,x
		op->cycles = 4;
		snprintf (addrbuf, addrsize,"x,0x%02x,+", (len > 1)? data[1]: 0);
		break;
	case 0x0d: // op $ffff
		op->cycles = 4;
		snprintf (addrbuf, addrsize,"0x%04x", (len > 2) ? (data[1] | data[2] << 8): 0);
		break;
	case 0x1d: // op $ffff,x
		// FIXME: Add 1 if page boundary is crossed.
		op->cycles = 4;
		snprintf (addrbuf, addrsize,"x,0x%04x,+", (len > 2) ? data[1] | data[2] << 8: 0);
		break;
	case 0x19: // op $ffff,y
		// FIXME: Add 1 if page boundary is crossed.
		op->cycles = 4;
		snprintf (addrbuf, addrsize,"y,0x%04x,+", (len > 2)? data[1] | data[2] << 8: 0);
		break;
	case 0x01: // op ($ff,x)
		op->cycles = 6;
		snprintf (addrbuf, addrsize,"x,0x%02x,+,[2]", (len > 1)? data[1]: 0);
		break;
	case 0x11: // op ($ff),y
		// FIXME: Add 1 if page boundary is crossed.
		op->cycles = 5;
		snprintf (addrbuf, addrsize,"y,0x%02x,[2],+", (len > 1) ? data[1]: 0);
		break;
	}
}