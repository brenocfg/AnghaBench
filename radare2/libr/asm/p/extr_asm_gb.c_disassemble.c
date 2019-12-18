#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_4__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int R_MAX (int /*<<< orphan*/ ,int) ; 
 int gbDisass (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *r_op, const ut8 *buf, int len) {
	int dlen = gbDisass(r_op,buf,len);
	return r_op->size = R_MAX (0, dlen);
}