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
union sctp_subtype {size_t primitive; } ;

/* Variables and functions */
 size_t SCTP_EVENT_PRIMITIVE_MAX ; 
 char const** sctp_primitive_tbl ; 

const char *sctp_pname(const union sctp_subtype id)
{
	if (id.primitive <= SCTP_EVENT_PRIMITIVE_MAX)
		return sctp_primitive_tbl[id.primitive];
	return "unknown_primitive";
}