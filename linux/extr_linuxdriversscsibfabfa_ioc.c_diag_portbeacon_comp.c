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
struct TYPE_2__ {int /*<<< orphan*/  link_e2e; int /*<<< orphan*/  state; } ;
struct bfa_diag_s {TYPE_1__ beacon; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* cbfn_beacon ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_diag_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
diag_portbeacon_comp(struct bfa_diag_s *diag)
{
	bfa_trc(diag, diag->beacon.state);
	diag->beacon.state = BFA_FALSE;
	if (diag->cbfn_beacon)
		diag->cbfn_beacon(diag->dev, BFA_FALSE, diag->beacon.link_e2e);
}