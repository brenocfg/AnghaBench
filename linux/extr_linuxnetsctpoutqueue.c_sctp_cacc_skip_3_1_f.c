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
struct TYPE_2__ {int /*<<< orphan*/  cacc_saw_newack; } ;
struct sctp_transport {TYPE_1__ cacc; } ;

/* Variables and functions */

__attribute__((used)) static inline int sctp_cacc_skip_3_1_f(struct sctp_transport *transport,
				       int count_of_newacks)
{
	if (count_of_newacks < 2 &&
			(transport && !transport->cacc.cacc_saw_newack))
		return 1;
	return 0;
}