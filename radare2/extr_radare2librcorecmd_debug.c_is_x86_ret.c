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

__attribute__((used)) static bool is_x86_ret(RDebug *dbg, ut64 addr) {
	ut8 buf[1];
	(void)dbg->iob.read_at (dbg->iob.io, addr, buf, R_ARRAY_SIZE (buf));
	switch (buf[0]) {
	case 0xc3:
	case 0xcb:
	case 0xc2:
	case 0xca:
		return true;
	default:
		return false;
	}
	/* Possibly incomplete with regard to instruction prefixes */
}