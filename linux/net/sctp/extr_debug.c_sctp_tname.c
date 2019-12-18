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
union sctp_subtype {scalar_t__ timeout; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ SCTP_EVENT_TIMEOUT_MAX ; 
 char const** sctp_timer_tbl ; 

const char *sctp_tname(const union sctp_subtype id)
{
	BUILD_BUG_ON(SCTP_EVENT_TIMEOUT_MAX + 1 != ARRAY_SIZE(sctp_timer_tbl));

	if (id.timeout < ARRAY_SIZE(sctp_timer_tbl))
		return sctp_timer_tbl[id.timeout];
	return "unknown_timer";
}