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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_5__ {int len; } ;
struct TYPE_4__ {TYPE_2__ buf; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int dcpu16_assemble (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ r_strbuf_get (TYPE_2__*) ; 

__attribute__((used)) static int assemble(RAsm *a, RAsmOp *op, const char *buf) {
	int len = dcpu16_assemble ((ut8*)r_strbuf_get (&op->buf), buf);
	op->buf.len = len;
	return len;
}