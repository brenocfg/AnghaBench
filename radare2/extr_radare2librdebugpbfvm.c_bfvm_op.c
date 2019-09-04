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
struct TYPE_4__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* read_at ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  eip; TYPE_1__ iob; } ;
typedef  TYPE_2__ BfvmCPU ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static ut8 bfvm_op(BfvmCPU *c) {
	// XXX: this is slow :(
	ut8 buf[4] = {0};
	if (c && c->iob.read_at && !c->iob.read_at (c->iob.io, c->eip, buf, 4)) {
		return 0xff;
	}
	return buf[0];
}