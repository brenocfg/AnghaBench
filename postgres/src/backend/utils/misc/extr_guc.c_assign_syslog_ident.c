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
 int /*<<< orphan*/  set_syslog_parameters (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog_facility ; 

__attribute__((used)) static void
assign_syslog_ident(const char *newval, void *extra)
{
#ifdef HAVE_SYSLOG
	set_syslog_parameters(newval, syslog_facility);
#endif
	/* Without syslog support, it will always be set to "none", so ignore */
}