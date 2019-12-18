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
struct TCP_Server_Info {int credits; int echo_credits; int oplock_credits; scalar_t__ in_flight; int /*<<< orphan*/  req_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
zero_credits(struct TCP_Server_Info *server)
{
	int val;

	spin_lock(&server->req_lock);
	val = server->credits + server->echo_credits + server->oplock_credits;
	if (server->in_flight == 0 && val == 0) {
		spin_unlock(&server->req_lock);
		return true;
	}
	spin_unlock(&server->req_lock);
	return false;
}