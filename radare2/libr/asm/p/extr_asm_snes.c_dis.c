#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_9__ {int M; int X; } ;
struct TYPE_8__ {int /*<<< orphan*/  pc; } ;
struct TYPE_7__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int snesDisass (int,int,int /*<<< orphan*/ ,TYPE_1__*,int const*,int) ; 
 TYPE_3__* snesflags ; 

__attribute__((used)) static int dis(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	int dlen = snesDisass (snesflags->M, snesflags->X, a->pc, op, buf, len);
	if (dlen < 0) {
		dlen = 0;
	}
	op->size = dlen;
	if (buf[0] == 0xc2) { //REP
		if (buf[1] & 0x10) {
			snesflags->X = 0;
		}
		if (buf[1] & 0x20) {
			snesflags->M = 0;
		}
	} else if (buf[0] == 0xe2) { //SEP
		if (buf[1] & 0x10) {
			snesflags->X = 1;
		}
		if (buf[1] & 0x20) {
			snesflags->M = 1;
		}
	}
	return dlen;
}