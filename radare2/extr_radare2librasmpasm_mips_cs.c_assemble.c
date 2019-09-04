#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_6__ {scalar_t__ big_endian; int /*<<< orphan*/  pc; } ;
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int mips_assemble (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ r_strbuf_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int assemble(RAsm *a, RAsmOp *op, const char *str) {
	ut8 *opbuf = (ut8*)r_strbuf_get (&op->buf);
	int ret = mips_assemble (str, a->pc, opbuf);
	if (a->big_endian) {
		ut8 *buf = opbuf;
		ut8 tmp = buf[0];
		buf[0] = buf[3];
		buf[3] = tmp;
		tmp = buf[1];
		buf[1] = buf[2];
		buf[2] = tmp;
	}
	return ret;
}