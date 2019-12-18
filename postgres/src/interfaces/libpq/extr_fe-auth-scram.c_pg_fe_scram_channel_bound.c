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
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  sasl_mechanism; } ;
typedef  TYPE_1__ fe_scram_state ;

/* Variables and functions */
 scalar_t__ FE_SCRAM_FINISHED ; 
 int /*<<< orphan*/  SCRAM_SHA_256_PLUS_NAME ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
pg_fe_scram_channel_bound(void *opaq)
{
	fe_scram_state *state = (fe_scram_state *) opaq;

	/* no SCRAM exchange done */
	if (state == NULL)
		return false;

	/* SCRAM exchange not completed */
	if (state->state != FE_SCRAM_FINISHED)
		return false;

	/* channel binding mechanism not used */
	if (strcmp(state->sasl_mechanism, SCRAM_SHA_256_PLUS_NAME) != 0)
		return false;

	/* all clear! */
	return true;
}