#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* read_at ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ iob; } ;
typedef  TYPE_2__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  R_ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_x86_call(RDebug *dbg, ut64 addr) {
	ut8 buf[3];
	ut8 *op = buf;
	(void)dbg->iob.read_at (dbg->iob.io, addr, buf, R_ARRAY_SIZE (buf));
	switch (buf[0]) {  /* Segment override prefixes */
	case 0x65:
	case 0x64:
	case 0x26:
	case 0x3e:
	case 0x36:
	case 0x2e:
		op++;
	}
	if (op[0] == 0xe8) {
		return true;
	}
	if (op[0] == 0xff  /* bits 4-5 (from right) of next byte must be 01 */
	    && (op[1] & 0x30) == 0x10) {
		return true;
	}
	/* ... */
	return false;
}