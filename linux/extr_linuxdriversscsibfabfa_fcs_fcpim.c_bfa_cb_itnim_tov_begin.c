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
struct bfa_fcs_itnim_s {TYPE_1__* rport; int /*<<< orphan*/  fcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  pwwn; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_cb_itnim_tov_begin(void *cb_arg)
{
	struct bfa_fcs_itnim_s *itnim = (struct bfa_fcs_itnim_s *) cb_arg;

	bfa_trc(itnim->fcs, itnim->rport->pwwn);
}