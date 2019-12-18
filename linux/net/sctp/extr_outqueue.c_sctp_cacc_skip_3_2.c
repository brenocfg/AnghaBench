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
struct TYPE_2__ {int /*<<< orphan*/  next_tsn_at_change; scalar_t__ cycling_changeover; } ;
struct sctp_transport {TYPE_1__ cacc; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ TSN_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sctp_cacc_skip_3_2(struct sctp_transport *primary, __u32 tsn)
{
	if (primary->cacc.cycling_changeover &&
	    TSN_lt(tsn, primary->cacc.next_tsn_at_change))
		return 1;
	return 0;
}