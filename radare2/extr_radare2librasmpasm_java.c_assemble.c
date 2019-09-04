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
struct TYPE_6__ {int /*<<< orphan*/  pc; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int r_java_assemble (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ r_strbuf_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int assemble(RAsm *a, RAsmOp *op, const char *input) {
	// TODO: get class info from bin if possible
	// XXX wrong usage of strbuf_get here
	return op->size = r_java_assemble (a->pc, (ut8*)r_strbuf_get (&op->buf), input);
}