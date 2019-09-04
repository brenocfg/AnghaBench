#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  op_status; } ;
struct bfa_s {TYPE_1__ iocfc; int /*<<< orphan*/  bfad; } ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_cb_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocfc_init_cb(void *bfa_arg, bfa_boolean_t complete)
{
	struct bfa_s	*bfa = bfa_arg;

	if (complete)
		bfa_cb_init(bfa->bfad, bfa->iocfc.op_status);
}