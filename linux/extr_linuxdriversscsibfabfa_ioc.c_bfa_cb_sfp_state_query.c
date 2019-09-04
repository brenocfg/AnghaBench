#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfa_sfp_s {int /*<<< orphan*/  (* state_query_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ state_query_lock; scalar_t__ portspeed; int /*<<< orphan*/  status; int /*<<< orphan*/  state_query_cbarg; int /*<<< orphan*/ * media; } ;

/* Variables and functions */
 scalar_t__ BFA_PORT_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  bfa_sfp_media_get (struct bfa_sfp_s*) ; 
 int /*<<< orphan*/  bfa_sfp_speed_valid (struct bfa_sfp_s*,scalar_t__) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_sfp_s*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_cb_sfp_state_query(struct bfa_sfp_s *sfp)
{
	bfa_trc(sfp, sfp->portspeed);
	if (sfp->media) {
		bfa_sfp_media_get(sfp);
		if (sfp->state_query_cbfn)
			sfp->state_query_cbfn(sfp->state_query_cbarg,
					sfp->status);
		sfp->media = NULL;
	}

	if (sfp->portspeed) {
		sfp->status = bfa_sfp_speed_valid(sfp, sfp->portspeed);
		if (sfp->state_query_cbfn)
			sfp->state_query_cbfn(sfp->state_query_cbarg,
					sfp->status);
		sfp->portspeed = BFA_PORT_SPEED_UNKNOWN;
	}

	sfp->state_query_lock = 0;
	sfp->state_query_cbfn = NULL;
}