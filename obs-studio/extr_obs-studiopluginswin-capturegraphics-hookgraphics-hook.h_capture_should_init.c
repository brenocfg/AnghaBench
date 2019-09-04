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

/* Variables and functions */
 int /*<<< orphan*/  capture_active () ; 
 scalar_t__ capture_alive () ; 
 scalar_t__ capture_restarted () ; 
 int /*<<< orphan*/  init_pipe () ; 
 int /*<<< orphan*/  ipc_pipe_client_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe ; 

__attribute__((used)) static inline bool capture_should_init(void)
{
	if (!capture_active() && capture_restarted()) {
		if (capture_alive()) {
			if (!ipc_pipe_client_valid(&pipe)) {
				init_pipe();
			}
			return true;
		}
	}

	return false;
}