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
struct TYPE_2__ {int /*<<< orphan*/  cycling_changeover; } ;
struct sctp_transport {TYPE_1__ cacc; } ;

/* Variables and functions */
 scalar_t__ sctp_cacc_skip_3_1_d (struct sctp_transport*,struct sctp_transport*,int) ; 
 scalar_t__ sctp_cacc_skip_3_1_f (struct sctp_transport*,int) ; 

__attribute__((used)) static inline int sctp_cacc_skip_3_1(struct sctp_transport *primary,
				     struct sctp_transport *transport,
				     int count_of_newacks)
{
	if (!primary->cacc.cycling_changeover) {
		if (sctp_cacc_skip_3_1_d(primary, transport, count_of_newacks))
			return 1;
		if (sctp_cacc_skip_3_1_f(transport, count_of_newacks))
			return 1;
		return 0;
	}
	return 0;
}