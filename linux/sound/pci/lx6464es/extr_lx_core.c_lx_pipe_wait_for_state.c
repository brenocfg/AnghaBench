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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct lx6464es {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int lx_pipe_state (struct lx6464es*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int lx_pipe_wait_for_state(struct lx6464es *chip, u32 pipe,
				  int is_capture, u16 state)
{
	int i;

	/* max 2*PCMOnlyGranularity = 2*1024 at 44100 = < 50 ms:
	 * timeout 50 ms */
	for (i = 0; i != 50; ++i) {
		u16 current_state;
		int err = lx_pipe_state(chip, pipe, is_capture, &current_state);

		if (err < 0)
			return err;

		if (!err && current_state == state)
			return 0;

		mdelay(1);
	}

	return -ETIMEDOUT;
}