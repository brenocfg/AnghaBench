#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_5__ {scalar_t__ cpu; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  int /*<<< orphan*/  RAnalOp ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int anal_pic_midrange_op (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int anal_pic_pic18_op (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 

__attribute__((used)) static int anal_pic_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	if (anal->cpu && strcasecmp (anal->cpu, "baseline") == 0) {
		// TODO: implement
		return -1;
	}
	if (anal->cpu && strcasecmp (anal->cpu, "midrange") == 0) {
		return anal_pic_midrange_op (anal, op, addr, buf, len);
	}
	if (anal->cpu && strcasecmp (anal->cpu, "pic18") == 0) {
		return anal_pic_pic18_op (anal, op, addr, buf, len);
	}
	return -1;
}