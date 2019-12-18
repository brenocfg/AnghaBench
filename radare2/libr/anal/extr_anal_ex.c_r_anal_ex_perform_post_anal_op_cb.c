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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {TYPE_1__* cur; scalar_t__ use_ex; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* post_anal_op_cb ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  RAnalState ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_anal_ex_perform_post_anal_op_cb(RAnal *anal, RAnalState *state, ut64 addr) {
	if (anal && anal->use_ex && anal->cur && anal->cur->post_anal_op_cb) {
		anal->cur->post_anal_op_cb (anal, state, addr);
	}
}