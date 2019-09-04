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
struct sctp_transport {scalar_t__ error_count; int /*<<< orphan*/  last_time_heard; } ;

/* Variables and functions */
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_transport *sctp_trans_elect_tie(struct sctp_transport *trans1,
						   struct sctp_transport *trans2)
{
	if (trans1->error_count > trans2->error_count) {
		return trans2;
	} else if (trans1->error_count == trans2->error_count &&
		   ktime_after(trans2->last_time_heard,
			       trans1->last_time_heard)) {
		return trans2;
	} else {
		return trans1;
	}
}