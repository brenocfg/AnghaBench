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
struct bfa_lps_s {int /*<<< orphan*/  uarg; TYPE_1__* bfa; scalar_t__ fdisc; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_cb_lps_fdisclogo_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_cb_lps_flogo_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_lps_logout_comp_cb(void *arg, bfa_boolean_t complete)
{
	struct bfa_lps_s *lps	= arg;

	if (!complete)
		return;

	if (lps->fdisc)
		bfa_cb_lps_fdisclogo_comp(lps->bfa->bfad, lps->uarg);
	else
		bfa_cb_lps_flogo_comp(lps->bfa->bfad, lps->uarg);
}