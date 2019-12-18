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
 int /*<<< orphan*/  set_syslog_parameters (char*,int) ; 
 char* syslog_ident_str ; 

__attribute__((used)) static void
assign_syslog_facility(int newval, void *extra)
{
#ifdef HAVE_SYSLOG
	set_syslog_parameters(syslog_ident_str ? syslog_ident_str : "postgres",
						  newval);
#endif
	/* Without syslog support, just ignore it */
}